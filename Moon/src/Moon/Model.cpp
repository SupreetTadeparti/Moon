#include "Model.hpp"

namespace Moon
{
	Model::Model(Geometry* geometry) : m_Shader(Shader::GetDefault()), m_Geometry(geometry), m_Material(Material::GetDefault()), m_Fixed(false)
	{
	}

	Model::Model(Geometry* geometry, Material* material) : m_Shader(Shader::GetDefault()), m_Geometry(geometry), m_Material(material), m_Fixed(false)
	{
	}

	Model::Model(Geometry* geometry, Shader* shader) : m_Shader(shader), m_Geometry(geometry), m_Material(Material::GetDefault()), m_Fixed(false)
	{
	}

	Model::Model(Geometry* geometry, Shader* shader, Material* material) : m_Shader(shader), m_Geometry(geometry), m_Material(material), m_Fixed(false)
	{
	}

	void Model::SetMaterial(Material* material)
	{
		m_Material = material;
	}

	void Model::SetShader(Shader* shader)
	{
		m_Shader = shader;
	}
}