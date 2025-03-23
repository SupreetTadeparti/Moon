#pragma once

#include "Core.h"
#include "VertexArray.hpp"
#include "Material.hpp"
#include "Geometry.hpp"

namespace Moon
{
	class Model
	{
	public:
		MOON_API Model(Geometry*);
		MOON_API Model(Geometry*, Material*);
		MOON_API Model(Geometry*, Shader*);
		MOON_API Model(Geometry*, Shader*, Material*);
		MOON_API void SetMaterial(Material*);
		MOON_API void SetShader(Shader*);
		MOON_API inline void SetFixed(Bool fixed) { m_Fixed = fixed; }
		MOON_API inline Geometry* GetGeometry() const { return m_Geometry; }
		MOON_API inline Material* GetMaterial() const { return m_Material; }
		MOON_API inline Shader* GetShader() const { return m_Shader; }
		MOON_API inline Bool GetFixed() const { return m_Fixed; }
		MOON_API inline Bool GetTransparency() const 
		{
			return m_Material->GetMaterialType() == MaterialType::Color ? m_Material->GetColor()->GetColor().a < 1 : false;
		}
	private:
		Geometry* m_Geometry;
		Material* m_Material;
		Shader* m_Shader;
		Bool m_Fixed;
	};
}
