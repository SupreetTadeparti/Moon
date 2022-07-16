#pragma once

#include "Core.h"
#include "VertexArray.hpp"
#include "Material.hpp"

namespace Moon
{
	class Model
	{
	public:
		Model(VertexArray*);
		Model(VertexArray*, Material*);
		Model(Shader*, VertexArray*);
		Model(Shader*, VertexArray*, Material*);
		void SetVertexArray(VertexArray*);
		void SetMaterial(Material*);
		void SetShader(Shader*);
		void Render() const;
		inline VertexArray* GetVertexArray() const { return m_VertexArray; }
		inline Material* GetMaterial() const { return m_Material; }
		inline Shader* GetShader() const { return m_Shader; }
	private:
		VertexArray* m_VertexArray;
		Material* m_Material;
		Shader* m_Shader;
		static const Vec4 s_DefaultColor;
	};
}
