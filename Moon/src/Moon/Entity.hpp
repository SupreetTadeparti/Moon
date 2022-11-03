#pragma once

#include "Core.h"
#include "Sprite.hpp"
#include "EventController.hpp"

namespace Moon
{
	class Entity : public CallbackEventController
	{
	public:
		MOON_API Entity(Model* model, Vec3 translation = Vec3(0.0f), Vec3 rotation = Vec3(0.0f), Vec3 scale = Vec3(1.0f));
		MOON_API Entity(Sprite* sprite, Vec3 translation = Vec3(0.0f), Vec3 rotation = Vec3(0.0f), Vec3 scale = Vec3(1.0f));
		MOON_API void Move(Vec3 translation);
		MOON_API void Rotate(Vec3 rotation);
		MOON_API void Scale(Vec3 scale);
		MOON_API inline void SetMaterial(Material* material) { m_Material = material; };
		MOON_API inline void SetFixed(Bool fixed) { m_Fixed = fixed; }
		MOON_API inline Bool GetFixed() { return m_Fixed; }
		MOON_API inline Vec3 GetPosition() const { return m_Translation; }
		MOON_API inline void SetPosition(Vec3 position) { m_Translation = position; UpdateTranslationMatrix(); }
		MOON_API inline Vec3 GetRotation() const { return m_Rotation; }
		MOON_API inline void SetRotation(Vec3 rotation) { m_Rotation = rotation; UpdateRotationMatrix(); }
		MOON_API inline Mat4 GetScaleMatrix() const { return m_ScaleMatrix; }
		MOON_API inline void SetScaleMatrix(Mat4 mat) { m_ScaleMatrix = mat; UpdateScaleMatrix(); }
		MOON_API inline Mat4 GetModelMatrix() const { return m_ModelMatrix; }
		MOON_API inline void SetModelMatrix(Mat4 mat) { m_ModelMatrix = mat; }
		MOON_API inline Mat4 GetTranslationMatrix() const { return m_TranslationMatrix; }
		MOON_API inline void SetTranslationMatrix(Mat4 mat) { m_TranslationMatrix = mat; }
		MOON_API inline Mat4 GetRotationMatrix() const { return m_RotationMatrix; }
		MOON_API inline void SetRotationMatrix(Mat4 mat) { m_RotationMatrix = mat; }
		MOON_API inline Material* const GetMaterial() const { return m_Material; }
		MOON_API inline Model* const GetModel() const { return m_Model; }
		MOON_API inline Bool GetTransparency() const 
		{
			return m_Material->GetMaterialType() == MaterialType::Color ? m_Material->GetColor()->GetColor().a < 1 : false;
		};
	private:
		void UpdateModelMatrix();
		void UpdateTranslationMatrix();
		void UpdateRotationMatrix();
		void UpdateScaleMatrix();
		Vec3 m_Translation;
		Vec3 m_Rotation;
		Vec3 m_Scale;
		Bool m_Fixed;
		Material* m_Material;
		Model* m_Model;
		Mat4 m_TranslationMatrix;
		Mat4 m_RotationMatrix;
		Mat4 m_ScaleMatrix;
		Mat4 m_ModelMatrix;
	};
}
