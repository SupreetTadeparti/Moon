#include "Scene.hpp"
#include "Buffer.hpp"

namespace Moon
{
	Scene::Scene() : m_Camera(nullptr), m_AmbientLight(nullptr), m_DirectionalLight(nullptr), m_SpotLight(nullptr), m_FirstIndex(0), m_BaseVertex(0), m_BaseInstance(0), m_First(true), m_BufferModified(false), m_Shader(Shader::GetDefault())
	{
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

	void Scene::UpdateModels()
	{
		if (m_First)
		{
			m_VertexArray = new VertexArray();

			List<Float> p;
			List<Float> tc;
			List<Float> n;
			List<Float> c;
			List<Uint> i;
			List<Uint> instanceCounts;

			for (Model* model : m_Models)
			{
				List<Float> positions = model->GetGeometry()->GetVertexData()->Positions;
				List<Float> texCoords = model->GetGeometry()->GetVertexData()->TextureCoords;
				List<Float> normals = model->GetGeometry()->GetVertexData()->Normals;
				List<Uint> indices = model->GetGeometry()->GetVertexData()->Indices;
				p.insert(p.end(), positions.begin(), positions.end());
				tc.insert(tc.end(), texCoords.begin(), texCoords.end());
				n.insert(n.end(), normals.begin(), normals.end());
				i.insert(i.end(), indices.begin(), indices.end());

				Uint instances = m_Indirect[m_IndirectIndices[model]].InstanceCount;
				Vec4 color = model->GetMaterial()->GetColor()->GetColor();

				for (Uint i = 0; i < instances; i++)
				{
					c.push_back(color.x); 
					c.push_back(color.y);
					c.push_back(color.z);
					c.push_back(color.a);
				}
			}

			List<Float> vertices = p;
			vertices.insert(vertices.end(), tc.begin(), tc.end());
			vertices.insert(vertices.end(), n.begin(), n.end());
			vertices.insert(vertices.end(), c.begin(), c.end());

			Buffer* buffer = new Buffer(vertices.data(), vertices.size());
			Buffer* indexBuffer = new Buffer(i.data(), i.size());

			IndexBuffer*  ibo  = new IndexBuffer(i.data(), i.size());
			VertexBuffer* pvbo = new VertexBuffer(0, 3, 0, 0, buffer);
			VertexBuffer* tvbo = new VertexBuffer(1, 2, 0, (p.size()) * sizeof(Float), buffer);
			VertexBuffer* nvbo = new VertexBuffer(2, 3, 0, (p.size() + tc.size()) * sizeof(Float), buffer);
			VertexBuffer* cvbo = new VertexBuffer(3, 4, 0, (p.size() + tc.size() + n.size()) * sizeof(Float), buffer, AttributeAdvanceRate::Shape);

			m_VertexArray->AddVBO(pvbo);
			m_VertexArray->AddVBO(tvbo);
			m_VertexArray->AddVBO(nvbo);
			m_VertexArray->AddVBO(cvbo);
			m_VertexArray->SetIBO(ibo);

			m_IndirectBuffer = new Buffer(m_Indirect.data(), m_Indirect.size(), BufferType::Indirect);

			m_VertexArray->SetIndirectBuffer(m_IndirectBuffer);

			m_TransformationBuffer = new Buffer(m_Transformations.data(), m_Transformations.size());

			for (Short i = 0; i < 4; i++)
			{
				VertexBuffer* vbo = new VertexBuffer(4 + i, 4, sizeof(Mat4), i * sizeof(Vec4), m_TransformationBuffer, AttributeAdvanceRate::Shape);
				m_VertexArray->AddVBO(vbo);
			}

			m_First = false;
			m_BufferModified = false;
		}

		if (m_BufferModified)
		{
			m_TransformationBuffer->SetData(m_Transformations.data(), m_Transformations.size());
			m_IndirectBuffer->SetData(m_Indirect.data(), m_Indirect.size());
			m_BufferModified = false;
		}

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
			
			m_Models.push_back(model);
		}
		
		m_Indirect[m_IndirectIndices[model]].InstanceCount++;
		m_BaseInstance++;

		for (Uint i = m_IndirectIndices[model] + 1; i < m_Indirect.size(); i++)
		{
			m_Indirect[i].BaseInstance++;
		}

		m_Entities.push_back(entity);
		m_Transformations.push_back(entity->GetModelMatrix());

		m_BufferModified = true;
	}

	void Scene::RemoveEntity(Entity* entity)
	{
		List<Entity*>::iterator idx = std::find(m_Entities.begin(), m_Entities.end(), entity);
		m_Entities.erase(idx);
		m_Transformations.erase(m_Transformations.begin() + (idx - m_Entities.begin()));
		m_TransformationBuffer->SetData(m_Transformations.data(), m_Transformations.size());
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