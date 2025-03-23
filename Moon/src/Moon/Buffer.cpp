#include "Buffer.hpp"
#include "Scene.hpp"

namespace Moon
{
	VertexBuffer::VertexBuffer(Int location, Int size, Int stride, Int pointer, Buffer* buffer, AttributeAdvanceRate rate, Uint divisor, List<Uint> divisors) : 
		m_Location(location), m_Size(size), m_Stride(stride), m_Pointer(pointer), 
		m_Buffer(buffer), m_Divisor(divisor), m_Divisors(divisors), m_AdvanceRate(rate)
	{
	}

	template <typename T>
	MOON_API Buffer::Buffer(T* data, Uint count, BufferType bt) : m_BufferType(bt)
	{
		glGenBuffers(1, &m_BufferID);
		SetData(data, count);
	}

	template <typename T>
	MOON_API void Buffer::SetData(T* data, Uint count)
	{
		if (m_BufferID == NULL)
		{
			return;
		}
		Bind();
		glBufferData((Int)m_BufferType, count * sizeof(T), data, GL_STATIC_DRAW);
		Unbind();
	}

	template <typename T>
	MOON_API void Buffer::UpdateData(T* data, Uint idx)
	{
		Bind();
		glBufferSubData((Int)m_BufferType, idx * sizeof(T), sizeof(T), data);
		Unbind();
	}

	template <typename T>
	MOON_API IndexBuffer::IndexBuffer(T* data, Uint count) : m_Count(count)
	{
		glGenBuffers(1, &m_BufferID);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(T), data, GL_STATIC_DRAW);
		Unbind();
	}

	template MOON_API Buffer::Buffer(Mat4* data, Uint count, BufferType bt);
	template MOON_API Buffer::Buffer(Double* data, Uint count, BufferType bt);
	template MOON_API Buffer::Buffer(Float* data, Uint count, BufferType bt);
	template MOON_API Buffer::Buffer(Int* data, Uint count, BufferType bt);
	template MOON_API Buffer::Buffer(Uint* data, Uint count, BufferType bt);
	template MOON_API Buffer::Buffer(RenderModel* data, Uint count, BufferType bt);
	template MOON_API void Buffer::SetData(Mat4* data, Uint count);
	template MOON_API void Buffer::SetData(Double* data, Uint count);
	template MOON_API void Buffer::SetData(Float* data, Uint count);
	template MOON_API void Buffer::SetData(Int* data, Uint count);
	template MOON_API void Buffer::UpdateData(Mat4* data, Uint count);
	template MOON_API void Buffer::UpdateData(Double* data, Uint count);
	template MOON_API void Buffer::UpdateData(Float* data, Uint count);
	template MOON_API void Buffer::UpdateData(Int* data, Uint count);
	template MOON_API IndexBuffer::IndexBuffer(Uint* data, Uint count);
}