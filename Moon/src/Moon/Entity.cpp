#include "Entity.hpp"
#include "Renderer.hpp"

namespace Moon
{
	Entity::Entity(Model* model, Vec3 translation, Vec3 rotation, Vec3 scale) : m_Model(model), m_Translation(translation), m_Rotation(rotation), m_Scale(scale)
	{
		m_TranslationMatrix = glm::translate(Mat4(1.0f), m_Translation);
		m_RotationMatrix = glm::rotate(Mat4(1.0f), m_Rotation[0], Vec3(1, 0, 0)) *
			glm::rotate(Mat4(1.0f), m_Rotation[1], Vec3(0, 1, 0)) *
			glm::rotate(Mat4(1.0f), m_Rotation[2], Vec3(0, 0, 1));
		m_ScaleMatrix = glm::scale(Mat4(1.0f), m_Scale);
		UpdateModelMatrix();
	}

	Entity::Entity(Sprite* sprite, Vec3 translation, Vec3 rotation, Vec3 scale) : m_Model(sprite->GetModel()), m_Translation(translation), m_Rotation(rotation), m_Scale(scale)
	{
		UpdateModelMatrix();
	}

	void Entity::Move(Vec3 translation)
	{
		m_Translation += translation;
		UpdateTranslationMatrix();
	}

	void Entity::Rotate(Vec3 rotation)
	{
		m_Rotation += rotation;
		UpdateRotationMatrix();
	}

	void Entity::Scale(Vec3 scale)
	{
		m_Scale += scale;
		UpdateScaleMatrix();
	}

	void Entity::UpdateModelMatrix()
	{
		m_ModelMatrix = m_TranslationMatrix * m_RotationMatrix * m_ScaleMatrix;
		Renderer::SetModified(true);
		m_Modified = true;
	}

	void Entity::UpdateTranslationMatrix()
	{
		m_TranslationMatrix = glm::translate(Mat4(1.0f), m_Translation);
		UpdateModelMatrix();
	}

	void Entity::UpdateRotationMatrix()
	{
		m_RotationMatrix = glm::rotate(Mat4(1.0f), m_Rotation[0], Vec3(1, 0, 0)) *
			glm::rotate(Mat4(1.0f), m_Rotation[1], Vec3(0, 1, 0)) *
			glm::rotate(Mat4(1.0f), m_Rotation[2], Vec3(0, 0, 1));
		UpdateModelMatrix();
	}

	void Entity::UpdateScaleMatrix()
	{
		m_ScaleMatrix = glm::scale(Mat4(1.0f), m_Scale);
		UpdateModelMatrix();
	}
}