#pragma once

#include "Core.h"
#include "VertexArray.hpp"
#include "Material.hpp"

namespace Moon
{
	class Model
	{
	public:
		MOON_API Model(Shape);
		MOON_API Model(VertexArray*);
		MOON_API Model(VertexArray*, Material*);
		MOON_API Model(Shader*, VertexArray*);
		MOON_API Model(Shader*, VertexArray*, Material*);
		MOON_API void SetVertexArray(VertexArray*);
		MOON_API void SetMaterial(Material*);
		MOON_API void SetShader(Shader*);
		MOON_API inline void SetFixed(Bool fixed) { m_Fixed = fixed; }
		MOON_API inline void SetModified(Bool modified) { m_Modified = modified; }
		MOON_API void Render(Int count=1) const;
		MOON_API inline VertexArray* GetVertexArray() const { return m_VertexArray; }
		MOON_API inline Material* GetMaterial() const { return m_Material; }
		MOON_API inline Shader* GetShader() const { return m_Shader; }
		MOON_API inline Bool GetFixed() const { return m_Fixed; }
		MOON_API inline Bool GetModified() const { return m_Modified; }
		MOON_API inline Bool GetTransparency() const 
		{
			return m_Material->GetMaterialType() == MaterialType::Color ? m_Material->GetColor()->GetColor().a < 1 : false;
		}
	private:
		VertexArray* m_VertexArray;
		Material* m_Material;
		Shader* m_Shader;
		Bool m_Modified;
		Bool m_Fixed;
	};
}
