#pragma once

#include "Core.h"
#include "Buffer.hpp"
#include "Shader.hpp"

namespace Moon
{
	class VertexArray
	{
	public:
		MOON_API VertexArray();
		MOON_API void AddVBO(VertexBuffer* vbo);
		MOON_API void SetIBO(IndexBuffer* ibo);
		MOON_API void SetIndirectBuffer(Buffer* indBuffer);
		MOON_API inline IndexBuffer* GetIndexBuffer() const { return m_IndexBuffer; };
		MOON_API inline Buffer* GetIndirectBuffer() const { return m_IndirectBuffer; };
		MOON_API inline void Bind() const;
		MOON_API inline void Unbind() const { glBindVertexArray(0); };
	private:
		Uint m_VertexArrayID;
		IndexBuffer* m_IndexBuffer;
		Buffer* m_IndirectBuffer;
		List<Float> m_Positions;
		List<Float> m_TextureCoords;
		List<Float> m_Normals;
		List<Uint> m_Indices;
	};
}