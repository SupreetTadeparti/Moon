#include "Model.hpp"

namespace Moon
{
	Model::Model(Shape shape) : m_Shader(Shader::GetDefault()), m_VertexArray(VertexArray::Default(shape)), m_Material(Material::GetDefault())
	{
	}

	Model::Model(VertexArray* vao) : m_Shader(Shader::GetDefault()), m_VertexArray(vao), m_Material(Material::GetDefault())
	{
	}

	Model::Model(VertexArray* vao, Material* material) : m_Shader(Shader::GetDefault()), m_VertexArray(vao), m_Material(material)
	{
	}

	Model::Model(Shader* shader, VertexArray* vao) : m_Shader(shader), m_VertexArray(vao), m_Material(Material::GetDefault())
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