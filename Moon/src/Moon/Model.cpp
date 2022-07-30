#include "Model.hpp"

namespace Moon
{
	const Vec4 Model::s_DefaultColor(255.0f / 2, 255.0f / 2, 255.0f / 2, 1.0f);

	Model::Model(VertexArray* vao) : m_Shader(Shader::GenerateDefaultColor()), m_VertexArray(vao), m_Material(new Material(new Color(s_DefaultColor)))
	{
	}

	Model::Model(VertexArray* vao, Material* material) : m_Shader(material->GetMaterialType() == MaterialType::Texture ? Shader::GenerateDefaultTexture() : Shader::GenerateDefaultColor()), m_VertexArray(vao), m_Material(material)
	{
	}

	Model::Model(Shader* shader, VertexArray* vao) : m_Shader(shader), m_VertexArray(vao), m_Material(new Material(new Color(s_DefaultColor)))
	{
	}

	Model::Model(Shader* shader, VertexArray* vao, Material* material) : m_Shader(shader), m_VertexArray(vao), m_Material(material)
	{
	}

	void Model::SetVertexArray(VertexArray* vao)
	{
		m_VertexArray = vao;
	}

	void Model::SetMaterial(Material* material)
	{
		m_Material = material;
	}

	void Model::SetShader(Shader* shader)
	{
		m_Shader = shader;
	}

	void Model::Render() const
	{
		m_VertexArray->Render();
	}
}