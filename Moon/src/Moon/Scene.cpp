#include "Scene.hpp"
#include "Buffer.hpp"

namespace Moon
{
	Scene::Scene() : m_Camera(nullptr), m_AmbientLight(nullptr), m_DirectionalLight(nullptr), m_SpotLight(nullptr), m_FirstIndex(0), m_BaseVertex(0), m_BaseInstance(0), m_First(true), m_EntityAdded(false), m_Shader(Shader::GetDefault()), m_IndexBuffer(nullptr), m_VertexDataBuffer(nullptr), m_IndirectBuffer(nullptr), m_TransformationBuffer(nullptr), m_VertexArray(nullptr), m_ShaderStorageBuffer(nullptr)
	{
	}

	Scene::~Scene()
	{
		delete m_VertexArray;
		delete m_IndirectBuffer;
		delete m_TransformationBuffer;
		delete m_ShaderStorageBuffer;
		delete m_IndexBuffer;
		delete m_VertexDataBuffer;

		for (VertexBuffer* vbo : m_VertexBuffers)
		{
			delete vbo;
		}
		
		for (Model* model : m_Models)
		{
			delete model;
		}
	}

	void Scene::Render()
	{
		m_Shader->Bind();
		//Material* material = model->GetMaterial();
		//switch (material->GetMaterialType())
		//{
		//case MaterialType::Color:
		//	m_Shader->SetUniformInt("u_FragmentType", 1);
		//	m_Shader->SetUniformVec4("u_Color", material->GetColor()->GetColor());
		//	break;
		//case MaterialType::Texture:
		//	m_Shader->SetUniformInt("u_FragmentType", 2);
		//	m_Shader->SetUniformInt("u_Texture", 0);
		//	material->GetTexture()->Bind(0);
		//	break;
		//}
		//Bool ambientLight = m_AmbientLight != nullptr;
		//m_Shader->SetUniformInt("u_AmbientLightActivated", ambientLight);
		//if (ambientLight)
		//{
		//	m_Shader->SetUniformVec3("u_AmbientLightColor", m_AmbientLight->GetColor() / 255.0f);
		//	m_Shader->SetUniformFloat("u_AmbientLightBrightness", m_AmbientLight->GetBrightness());
		//}
		//Bool directionalLight = m_DirectionalLight != nullptr;
		//m_Shader->SetUniformInt("u_DirectionalLightActivated", directionalLight);
		//if (directionalLight)
		//{
		//	m_Shader->SetUniformVec3("u_DirectionalLightColor", m_DirectionalLight->GetColor() / 255.0f);
		//	m_Shader->SetUniformVec3("u_DirectionalLightDirection", m_DirectionalLight->GetDirection());
		//}
		if (m_Models.empty()) return;

		if (m_Camera != nullptr)
		{
			m_Shader->SetView(m_Camera->GetViewMatrix());
		}
		//m_Shader->SetUniformInt("u_Fixed", model->GetFixed());
		m_VertexArray->Bind();
		m_VertexArray->GetIndexBuffer()->Bind();
		m_VertexArray->GetIndirectBuffer()->Bind();

		glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, (const void*)0, m_Models.size(), 0);

		m_VertexArray->GetIndirectBuffer()->Unbind();
		m_VertexArray->GetIndexBuffer()->Unbind();
		m_VertexArray->Unbind();
		m_Shader->Unbind();
	}

	void Scene::AddModelVertexData(Model* model)
	{
		List<Float>* p = m_VertexArray->GetPositions();
		List<Float>* tc = m_VertexArray->GetTextureCoords();
		List<Float>* n = m_VertexArray->GetNormals();
		//List<Float>* c = m_VertexArray->GetColors();
		List<Uint>* i = m_VertexArray->GetIndices();

		// TODO: Prevent vector copying
		List<Float> positions = model->GetGeometry()->GetVertexData()->Positions;
		List<Float> texCoords = model->GetGeometry()->GetVertexData()->TextureCoords;
		List<Float> normals = model->GetGeometry()->GetVertexData()->Normals;
		List<Uint> indices = model->GetGeometry()->GetVertexData()->Indices;
		p->insert(p->end(), positions.begin(), positions.end());
		tc->insert(tc->end(), texCoords.begin(), texCoords.end());
		n->insert(n->end(), normals.begin(), normals.end());
		i->insert(i->end(), indices.begin(), indices.end());

		// TODO: Fix color system. Add color per entity rather than at once for model (since we don't know number of instances before hand). Ideally have color once per model.
		//Uint instances = m_Indirect[m_IndirectIndices[model]].InstanceCount;
		//Vec4 color = model->GetMaterial()->GetColor()->GetColor();

		//for (Uint i = 0; i < 100; i++)
		//{
		//	c->push_back(color.x);
		//	c->push_back(color.y);
		//	c->push_back(color.z);
		//	c->push_back(color.a);
		//}
	}

	void Scene::InitVertexData()
	{
		m_VertexArray = new VertexArray();

		m_VertexDataBuffer = new Buffer((Float*)nullptr, 0);

		m_IndexBuffer = new Buffer((Uint*)nullptr, 0, BufferType::ElementArray);

		m_VertexArray->SetIBO(m_IndexBuffer);

		// TODO: Do we need VertexBuffers? Do we need to heap allocate all these and store them in a vector when we can just directly supply them to the VertexArray?
		m_VertexBuffers.push_back(new VertexBuffer(0, 3, 0, 0, m_VertexDataBuffer));
		m_VertexBuffers.push_back(new VertexBuffer(1, 2, 0, 0, m_VertexDataBuffer));
		m_VertexBuffers.push_back(new VertexBuffer(2, 3, 0, 0, m_VertexDataBuffer));
		//m_VertexBuffers.push_back(new VertexBuffer(3, 4, 0, 0, m_VertexDataBuffer, AttributeAdvanceRate::Shape));

		for (VertexBuffer* vbo : m_VertexBuffers)
		{
			m_VertexArray->SetVBO(vbo);
		}

		m_IndirectBuffer = new Buffer((RenderModel*)nullptr, 0, BufferType::Indirect);

		m_VertexArray->SetIndirectBuffer(m_IndirectBuffer);

		m_TransformationBuffer = new Buffer((Mat4*)nullptr, 0);

		for (Short i = 0; i < 4; i++)
		{
			VertexBuffer* vbo = new VertexBuffer(3 + i, 4, sizeof(Mat4), i * sizeof(Vec4), m_TransformationBuffer, AttributeAdvanceRate::Shape);
			m_VertexArray->SetVBO(vbo);
		}

		m_EntityAdded = false;
	}

	void Scene::AddModel(Model* model)
	{
		// Update m_VertexDataBuffer
		AddModelVertexData(model);

		List<Float>* p = m_VertexArray->GetPositions();
		List<Float>* tc = m_VertexArray->GetTextureCoords();
		List<Float>* n = m_VertexArray->GetNormals();
		//List<Float>* c = m_VertexArray->GetColors();

		List<Float>* vertices = Util::ConcatLists({ p, tc, n });

		m_VertexDataBuffer->SetData(vertices->data(), vertices->size());

		// Update index buffer class
		List<Uint>* i = m_VertexArray->GetIndices();
		m_IndexBuffer->SetData(i->data(), i->size());

		// Update vertex buffer class
		m_VertexBuffers[1]->SetPointer((p->size()) * sizeof(Float));
		m_VertexBuffers[2]->SetPointer((p->size() + tc->size()) * sizeof(Float));
		//m_VertexBuffers[3]->SetPointer((p->size() + tc->size() + n->size()) * sizeof(Float));

		// Update vertex buffer data (vertex array class)

		for (VertexBuffer* vbo : m_VertexBuffers)
		{
			m_VertexArray->SetVBO(vbo);
		}

		m_Models.push_back(model);
	}

	void Scene::UpdateEntities()
	{
		// Update indirect and transformation buffer with new entity data
		if (m_EntityAdded)
		{
			m_TransformationBuffer->SetData(m_Transformations.data(), m_Transformations.size());
			m_IndirectBuffer->SetData(m_Indirect.data(), m_Indirect.size());
			m_EntityAdded = false;
		}

		// Update transformation buffer with modified entity transformations
		for (Uint i = 0; i < m_Entities.size(); i++)
		{
			Entity* entity = m_Entities[i];
			if (entity->GetModified())
			{
				Mat4 transformation = entity->GetModelMatrix();
				m_TransformationBuffer->UpdateData(&transformation, i);
				entity->SetModified(false);
			}
		}
	}

	void Scene::AddEntity(Entity* entity)
	{
		// Scene loads first entity
		if (m_First)
		{
			InitVertexData();
			m_First = false;
		}

		Model* model = entity->GetModel();

		// If model not seen before:
		if (m_IndirectIndices.find(model) == m_IndirectIndices.end())
		{
			m_IndirectIndices[model] = m_Indirect.size(); // Number of prior models

			// Number of vertices (non-repetitive) in model
			Uint vertexCount = model->GetGeometry()->GetVertexData()->Positions.size() / 3; 
			// Number of indices in model
			Uint indices = model->GetGeometry()->GetVertexData()->Indices.size();
			
			RenderModel rm = { indices, 0, m_FirstIndex, m_BaseVertex, m_BaseInstance };

			m_Indirect.push_back(rm);
			m_FirstIndex += indices;
			m_BaseVertex += vertexCount;
			
			AddModel(model);
		}
		
		m_Indirect[m_IndirectIndices[model]].InstanceCount++;
		m_BaseInstance++;

		for (Uint i = m_IndirectIndices[model] + 1; i < m_Indirect.size(); i++)
		{
			m_Indirect[i].BaseInstance++;
		}

		m_Entities.push_back(entity);
		m_Transformations.push_back(entity->GetModelMatrix());

		m_EntityAdded = true;
	}

	void Scene::RemoveEntity(Entity* entity)
	{
		// TODO: Handle removal of models and update m_Indirect accordingly
		List<Entity*>::iterator idx = std::find(m_Entities.begin(), m_Entities.end(), entity);
		m_Entities.erase(idx);
		m_Transformations.erase(m_Transformations.begin() + (idx - m_Entities.begin()));
		m_TransformationBuffer->SetData(m_Transformations.data(), m_Transformations.size());
		m_Indirect[m_IndirectIndices[entity->GetModel()]].InstanceCount--;
		if (m_Indirect[m_IndirectIndices[entity->GetModel()]].InstanceCount == 0)
		{
			m_Indirect.erase(m_Indirect.begin() + m_IndirectIndices[entity->GetModel()]);
			m_IndirectIndices.erase(entity->GetModel());
			m_Models.erase(std::remove(m_Models.begin(), m_Models.end(), entity->GetModel()), m_Models.end());

			// TODO: Update buffers to remove model

		}
		delete entity;
	}

	void Scene::SetCameraController(CameraController* cc)
	{
		if (m_Camera == nullptr) m_Camera = cc->GetCamera();

		AddChildCallback(cc, EventType::MouseMove, [](Vec2) -> bool { return true; });
		AddChildCallback(cc, EventType::Update, []() -> bool { return true; });
	}

	void Scene::AddText(Text* text)
	{
		for (Entity* entity : text->GetCharacters())
		{
			AddEntity(entity);
		}
	}
}