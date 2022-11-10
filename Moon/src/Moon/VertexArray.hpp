#pragma once

#include "Core.h"
#include "Buffer.hpp"
#include "Shader.hpp"

namespace Moon
{
	enum class MOON_API Shape
	{
		Rect, Box, Sphere
	};

	class MOON_API VertexArray
	{
	public:
		VertexArray();
		void AddVBO(VertexBuffer* vbo);
		void SetIBO(IndexBuffer* ibo);
		void Render(Int count=1) const;
		inline IndexBuffer* GetIndexBuffer() const { return m_IndexBuffer; };
		inline void Bind() const { glBindVertexArray(m_VertexArrayID); };
		inline void Unbind() const { glBindVertexArray(0); };

		static VertexArray* Default(Shape);
		static VertexArray* DefaultRect();
		static VertexArray* DefaultBox();
		static VertexArray* DefaultSphere();
	private:
		Uint m_VertexArrayID;
		IndexBuffer* m_IndexBuffer;
	};
}