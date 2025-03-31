#include "VertexArray.hpp"

namespace Moon
{
	VertexArray::VertexArray() : m_IndexBuffer(nullptr), m_IndirectBuffer(nullptr), m_VertexArrayID(0)
	{
		glGenVertexArrays(1, &m_VertexArrayID);
	}

	void VertexArray::SetIndirectBuffer(Buffer* buffer)
	{
		m_IndirectBuffer = buffer;
	}

	void VertexArray::SetIBO(Buffer* ibo)
	{
		m_IndexBuffer = ibo;
	}

	void VertexArray::SetVBO(VertexBuffer* vbo) const
	{
		Bind();
		vbo->GetBuffer()->Bind();

		Int location = vbo->GetLocation();
		Int size = vbo->GetSize();
		Int stride = vbo->GetStride();
		Int pointer = vbo->GetPointer();
		Uint divisor = vbo->GetDivisor();
		AttributeAdvanceRate rate = vbo->GetAdvanceRate();
		
		glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, (void*)pointer);
		glEnableVertexAttribArray(location);
		if (rate == AttributeAdvanceRate::Shape) glVertexAttribDivisor(location, 1);
		if (rate == AttributeAdvanceRate::Custom) glVertexAttribDivisor(location, divisor);
		if (rate == AttributeAdvanceRate::DynamicCustom)
		{
			// TODO: Implement dynamic custom attribute advance rate
		}
		
		vbo->GetBuffer()->Unbind();
		Unbind();
	}

	inline void VertexArray::Bind() const 
	{ 
		glBindVertexArray(m_VertexArrayID);
	};
}