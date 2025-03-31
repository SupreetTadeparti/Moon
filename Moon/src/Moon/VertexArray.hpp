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
		MOON_API void SetVBO(VertexBuffer* vbo) const;
		MOON_API inline void Bind() const;
		MOON_API inline void Unbind() const { glBindVertexArray(0); };

		MOON_API void SetIBO(Buffer* ibo); // TODO: Change IBO to IndexBuffer for consistency
		MOON_API void SetIndirectBuffer(Buffer* indBuffer);
		MOON_API inline Buffer* GetIndexBuffer() const { return m_IndexBuffer; };
		MOON_API inline Buffer* GetIndirectBuffer() const { return m_IndirectBuffer; };
		MOON_API inline List<Float>* GetPositions() { return &m_Positions; }
		MOON_API inline List<Float>* GetTextureCoords() { return &m_TextureCoords; }
		MOON_API inline List<Float>* GetNormals() { return &m_Normals; }
		MOON_API inline List<Uint>* GetIndices() { return &m_Indices; }

	private:
		Uint m_VertexArrayID;
		Buffer* m_IndexBuffer;
		Buffer* m_IndirectBuffer;
		List<Float> m_Positions;
		List<Float> m_TextureCoords;
		List<Float> m_Normals;
		List<Uint> m_Indices;
	};
}
