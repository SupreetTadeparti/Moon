#include "Model.hpp"

namespace Moon
{
	Model::Model(Shape shape) : m_Shader(Shader::GetDefault()), m_VertexArray(VertexArray::Default(shape)), m_Material(Material::GetDefault()), m_Fixed(false), m_Modified(false)
	{
	}

	Model::Model(VertexArray* vao) : m_Shader(Shader::GetDefault()), m_VertexArray(vao), m_Material(Material::GetDefault()), m_Fixed(false), m_Modified(false)
	{
	}

	Model::Model(VertexArray* vao, Material* material) : m_Shader(Shader::GetDefault()), m_VertexArray(vao), m_Material(material), m_Fixed(false), m_Modified(false)
	{
	}

	Model::Model(Shader* shader, VertexArray* vao) : m_Shader(shader), m_VertexArray(vao), m_Material(Material::GetDefault()), m_Fixed(false), m_Modified(false)
	{
	}

	Model::Model(Shader* shader, VertexArray* vao, Material* material) : m_Shader(shader), m_VertexArray(vao), m_Material(material), m_Fixed(false), m_Modified(false)
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

	void Model::Render(Int count) const
	{
		m_VertexArray->Render(count);
	}
}