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
		MOON_API void Render() const;
		MOON_API inline VertexArray* GetVertexArray() const { return m_VertexArray; }
		MOON_API inline Material* GetMaterial() const { return m_Material; }
		MOON_API inline Shader* GetShader() const { return m_Shader; }
	private:
		VertexArray* m_VertexArray;
		Material* m_Material;
		Shader* m_Shader;
	};
}
