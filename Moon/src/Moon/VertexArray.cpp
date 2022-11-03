#include "VertexArray.hpp"

namespace Moon
{
	VertexArray* VertexArray::s_RectVertexArray = nullptr;
	VertexArray* VertexArray::s_BoxVertexArray = nullptr;
	VertexArray* VertexArray::s_SphereVertexArray = nullptr;

	VertexArray::VertexArray() : m_IndexBuffer(nullptr)
	{
		glGenVertexArrays(1, &m_VertexArrayID);
	}

	void VertexArray::SetIBO(IndexBuffer* ibo)
	{
		m_IndexBuffer = ibo;
	}

	void VertexArray::AddVBO(VertexBuffer* vbo)
	{
		Bind();
		vbo->GetBuffer()->Bind();
		Int location = vbo->GetLocation();
		Int size = vbo->GetSize();
		Int stride = vbo->GetStride();
		Int64 pointer = vbo->GetPointer();
		glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, (void*)pointer);
		glEnableVertexAttribArray(location);
		vbo->GetBuffer()->Unbind();
		Unbind();
	}

	void VertexArray::Render()
	{
		glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, 0);
	}

	VertexArray* VertexArray::DefaultRect()
	{
		if (s_RectVertexArray != nullptr) return s_RectVertexArray;

		Float vertices[] = {
			// Positions
			-0.5, -0.5,
			0.5, -0.5,
			0.5, 0.5,
			-0.5, 0.5,

		  // Texture Coordinates
		  0, 0,
		  1, 0,
		  1, 1,
		  0, 1
		};

		Uint indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		Buffer* buffer = new Buffer(vertices, sizeof(vertices) / sizeof(Float));

		IndexBuffer* ibo = new IndexBuffer(indices, sizeof(indices) / sizeof(Uint));

		VertexBuffer* vbo = new VertexBuffer(0, 2, 0, 0, buffer);
		VertexBuffer* tvbo = new VertexBuffer(1, 2, 0, 8 * sizeof(Float), buffer);

		VertexArray* vao = new VertexArray();

		vao->AddVBO(vbo);
		vao->AddVBO(tvbo);
		vao->SetIBO(ibo);

		s_RectVertexArray = vao;

		return s_RectVertexArray;
	}

	VertexArray* VertexArray::DefaultBox()
	{
		if (s_BoxVertexArray != nullptr) return s_BoxVertexArray;


		/*
			Vertices Group Order :-
			0 - Back
			1 - Front
			2 - Right
			3 - Left
			4 - Top
			5 - Bottom
		*/

		Float vertices[] = {

			// Positions
			-0.5, 0.5, -0.5,
			-0.5, -0.5, -0.5,
			 0.5, -0.5, -0.5,
			 0.5, 0.5, -0.5,

			-0.5, 0.5, 0.5,
			-0.5, -0.5, 0.5,
			 0.5, -0.5, 0.5,
			 0.5, 0.5, 0.5,

			 0.5, 0.5, -0.5,
			 0.5, -0.5, -0.5,
			 0.5, -0.5, 0.5,
			 0.5, 0.5, 0.5,

			-0.5, 0.5, -0.5,
			-0.5, -0.5, -0.5,
			-0.5, -0.5, 0.5,
			-0.5, 0.5, 0.5,

			-0.5, 0.5, 0.5,
			-0.5, 0.5, -0.5,
			 0.5, 0.5, -0.5,
			 0.5, 0.5, 0.5,

			-0.5, -0.5, 0.5,
			-0.5, -0.5, -0.5,
			 0.5, -0.5, -0.5,
			 0.5, -0.5, 0.5,

			 // Texture Coordinates
			 0, 1, 0, 0, 1, 0, 1, 1,
			 1, 1, 1, 0, 0, 0, 0, 1,
			 0, 1, 0, 0, 1, 0, 1, 1,
			 1, 1, 1, 0, 0, 0, 0, 1,
			 1, 0, 1, 1, 0, 1, 0, 0,
			 1, 1, 1, 0, 0, 0, 0, 1,

			 // Normals
			 0,	 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
			 0,	 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1,
			 1,	 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,
			-1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0,
			 0,	 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,
			 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0,
		};

		Uint indices[] = {
			0, 1, 3,
			3, 1, 2,
			4, 5, 7,
			7, 5, 6,
			8, 9, 11,
			11, 9, 10,
			12, 13, 15,
			15, 13, 14,
			16, 17, 19,
			19, 17, 18,
			20, 21, 23,
			23, 21, 22
		};


		Buffer* buffer = new Buffer(vertices, sizeof(vertices) / sizeof(Float));

		IndexBuffer* ibo = new IndexBuffer(indices, sizeof(indices) / sizeof(Uint));

		VertexBuffer* vbo = new VertexBuffer(0, 3, 0, 0, buffer);
		VertexBuffer* tvbo = new VertexBuffer(1, 2, 0, 72 * sizeof(Float), buffer);
		VertexBuffer* nvbo = new VertexBuffer(2, 3, 0, 120 * sizeof(Float), buffer);

		VertexArray* vao = new VertexArray();

		vao->AddVBO(vbo);
		vao->AddVBO(tvbo);
		vao->AddVBO(nvbo);
		vao->SetIBO(ibo);

		s_BoxVertexArray = vao;

		return s_BoxVertexArray;
	}

	VertexArray* VertexArray::DefaultSphere()
	{
		if (s_SphereVertexArray != nullptr) return s_SphereVertexArray;

		List<Float> positions;
		List<Float> texCoords;
		List<Float> normals;
		List<Uint> indices;
		Float radius = 1.0f;
		Int stackCount = 30;
		Int sectorCount = 30;
		LongDouble sectorStep = 2 * Math::PI / sectorCount;
		LongDouble stackStep = Math::PI / stackCount;
		Float lengthInv = 1.0f / radius;
		Int k1;
		Int k2;
		Float s;
		Float t;
		Float x;
		Float y;
		Float z;
		Float xy;
		Float nx;
		Float ny;
		Float nz;
		Float stackAngle;
		Float sectorAngle;
		for (int i = 0; i <= stackCount; i++)
		{
			stackAngle = Math::PI / 2 - i * stackStep;
			xy = radius * cosf(stackAngle);
			z = radius * sinf(stackAngle);
			for (int j = 0; j <= sectorCount; j++)
			{
				sectorAngle = j * sectorStep;

				x = xy * cosf(sectorAngle);
				y = xy * sinf(sectorAngle);
				positions.push_back(x);
				positions.push_back(y);
				positions.push_back(z);

				nx = x * lengthInv;
				ny = y * lengthInv;
				nz = z * lengthInv;
				normals.push_back(nx);
				normals.push_back(ny);
				normals.push_back(nz);

				s = j / sectorCount;
				t = i / stackCount;
				texCoords.push_back(s);
				texCoords.push_back(t);
			}
			if (i != stackCount)
			{
				k1 = i * (sectorCount + 1);
				k2 = k1 + sectorCount + 1;
				for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
				{
					if (i != 0)
					{
						indices.push_back(k1);
						indices.push_back(k2);
						indices.push_back(k1 + 1);
					}
					if (i != (stackCount - 1))
					{
						indices.push_back(k1 + 1);
						indices.push_back(k2);
						indices.push_back(k2 + 1);
					}
				}
			}
		}

		List<Float> vertices;
		vertices.reserve(positions.size() + texCoords.size() + normals.size());
		vertices.insert(vertices.end(), positions.begin(), positions.end());
		vertices.insert(vertices.end(), texCoords.begin(), texCoords.end());
		vertices.insert(vertices.end(), normals.begin(), normals.end());

		Buffer* buffer = new Buffer(&vertices[0], vertices.size());

		IndexBuffer* ibo = new IndexBuffer(&indices[0], indices.size());

		VertexBuffer* vbo = new VertexBuffer(0, 3, 0, 0, buffer);
		VertexBuffer* tvbo = new VertexBuffer(1, 2, 0, positions.size() * sizeof(Float), buffer);
		VertexBuffer* nvbo = new VertexBuffer(2, 3, 0, (positions.size() + texCoords.size()) * sizeof(Float), buffer);

		VertexArray* vao = new VertexArray();

		vao->AddVBO(vbo);
		vao->AddVBO(tvbo);
		vao->AddVBO(nvbo);
		vao->SetIBO(ibo);

		s_SphereVertexArray = vao;

		return s_SphereVertexArray;
	}

	VertexArray* VertexArray::Default(Shape shape)
	{
		switch (shape)
		{
		case Shape::Rect:
			return DefaultRect();
			break;
		case Shape::Box:
			return DefaultBox();
			break;
		case Shape::Sphere:
			return DefaultSphere();
			break;
		}
		return nullptr;
	}
}