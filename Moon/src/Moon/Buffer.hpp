#pragma once

#include "Core.h"

namespace Moon
{
	enum class MOON_API AttributeAdvanceRate
	{
		Vertex,
		Shape,
		Custom,
		DynamicCustom
	};

	enum class MOON_API BufferType
	{
		Array=GL_ARRAY_BUFFER,
		ElementArray=GL_ELEMENT_ARRAY_BUFFER,
		Indirect=GL_DRAW_INDIRECT_BUFFER
	};

	class Buffer
	{
	public:
		template <typename T>
		MOON_API Buffer(T* data, Uint count, BufferType bt=BufferType::Array);
		template <typename T>
		MOON_API void SetData(T* data, Uint count);
		template <typename T>
		MOON_API void UpdateData(T* data, Uint idx);
		MOON_API inline void Bind() const { glBindBuffer((Int)m_BufferType, m_BufferID); };
		MOON_API inline void Unbind() const { glBindBuffer((Int)m_BufferType, 0); };
		MOON_API inline Uint GetID() const { return m_BufferID; };
	private:
		BufferType m_BufferType;
		Uint m_BufferID;
	};

	class MOON_API IndexBuffer
	{
	public:
		template <typename T>
		MOON_API IndexBuffer(T* data, Uint count);
		inline void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID); };
		inline void Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); };
		inline Uint GetID() const { return m_BufferID; };
		inline Uint GetCount() const { return m_Count; };
	private:
		Uint m_BufferID;
		Uint m_Count;
	};

	class MOON_API VertexBuffer
	{
	public:
		VertexBuffer(Int location, Int size, Int stride, Int pointer, Buffer* buffer, AttributeAdvanceRate rate = AttributeAdvanceRate::Vertex, Uint divisor=0, List<Uint> divisors={});

		// Getters
		inline Int GetLocation() const { return m_Location; }
		inline Int GetSize() const { return m_Size; }
		inline Int GetStride() const { return m_Stride; }
		inline Int GetPointer() const { return m_Pointer; }
		inline Uint GetDivisor() const { return m_Divisor; }
		inline List<Uint> GetDivisors() const { return m_Divisors; }
		inline Buffer* GetBuffer() const { return m_Buffer; }
		inline AttributeAdvanceRate GetAdvanceRate() const { return m_AdvanceRate; }
	private:
		Int m_Location;
		Int m_Size;
		Int m_Stride;
		Int m_Pointer;
		Uint m_Divisor;
		List<Uint> m_Divisors;
		Buffer* m_Buffer;
		AttributeAdvanceRate m_AdvanceRate;
	};
}