#include "Geometry.hpp"

namespace Moon
{
	HashMap<GeometryType, VertexData*> Geometry::s_DefaultVertexData;

	VertexData::VertexData(List<Float> p, List<Float> tc, List<Float> n, List<Uint> i) : Positions(p), TextureCoords(tc), Normals(n), Indices(i)
	{
	}

	void Geometry::Init()
	{
		// Rect
		VertexData* rectVertexData = new VertexData();

		rectVertexData->Positions = {
			-0.5, -0.5, 0,
			 0.5, -0.5, 0,
			 0.5,  0.5, 0,
			-0.5,  0.5, 0,
		};

		rectVertexData->TextureCoords = {
			0, 0,
			1, 0,
			1, 1,
			0, 1
		};

		rectVertexData->Indices = {
			0, 1, 2,
			2, 3, 0
		};
		
		// Box
		VertexData* boxVertexData = new VertexData();

		boxVertexData->Positions = {
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
			 0.5, -0.5, 0.5
		};

		boxVertexData->TextureCoords = {
			 0, 1, 0, 0, 1, 0, 1, 1,
			 1, 1, 1, 0, 0, 0, 0, 1,
			 0, 1, 0, 0, 1, 0, 1, 1,
			 1, 1, 1, 0, 0, 0, 0, 1,
			 1, 0, 1, 1, 0, 1, 0, 0,
			 1, 1, 1, 0, 0, 0, 0, 1,
		};

		boxVertexData->Normals = {
			 0,	 0,  1,  0,  0,  1,  0,  0,  1,  0,  0,  1,
			 0,	 0, -1,  0,  0, -1,  0,  0, -1,  0,  0, -1,
			 1,	 0,  0,  1,  0,  0,  1,  0,  0,  1,  0,  0,
			-1,  0,  0, -1,  0,  0, -1,  0,  0, -1,  0,  0,
			 0,	 1,  0,  0,  1,  0,  0,  1,  0,  0,  1,  0,
			 0, -1,  0,  0, -1,  0,  0, -1,  0,  0, -1,  0,
		};

		boxVertexData->Indices = {
			0,  1,  3,
			3,  1,  2,
			4,  5,  7,
			7,  5,  6,
			8,  9,  11,
			11, 9,  10,
			12, 13, 15,
			15, 13, 14,
			16, 17, 19,
			19, 17, 18,
			20, 21, 23,
			23, 21, 22
		};

		// Sphere
		VertexData* sphereVertexData = new VertexData();

		List<Float> positions;
		List<Float> texCoords;
		List<Float> normals;
		List<Uint> indices;
		Float radius = 1.0f;
		Int stackCount = 10;
		Int sectorCount = 10;
		LongDouble sectorStep = 2 * Math::PI / sectorCount;
		LongDouble stackStep = Math::PI / stackCount;
		Float lengthInv = 1.0f / radius;
		Int k1, k2;
		Float s, t, x, y, z, xy, nx, ny, nz, stackAngle, sectorAngle;
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

		sphereVertexData->Positions = positions;
		sphereVertexData->TextureCoords = texCoords;
		sphereVertexData->Normals = normals;
		sphereVertexData->Indices = indices;

		// Updating static vertex data
		s_DefaultVertexData[GeometryType::Rect] = rectVertexData;
		s_DefaultVertexData[GeometryType::Box] = boxVertexData;
		s_DefaultVertexData[GeometryType::Sphere] = sphereVertexData;
	}

	Geometry::Geometry(GeometryType shape)
	{
		m_VertexData = s_DefaultVertexData[shape];
	}

	Geometry::Geometry(const String& path)
	{
		m_VertexData = LoadOBJ(path);
	}

	List<String> Geometry::SplitString(const String& string, Char delimeter)
	{
		List<String> res;
		String curr;
		for (Char c : string)
		{
			if (c == delimeter)
			{
				res.push_back(curr);
				curr = "";
			}
			else curr += c;
		}
		res.push_back(curr);
		return res;
	}

	VertexData* Geometry::LoadOBJ(const String& path)
	{
		std::ifstream objfile("./src/models/" + path);

		if (objfile.fail()) MoonLogCritical("Failed to Load Model " + path);

		String line;

		List<Vec2> t;
		List<Vec3> n;

		List<Float> positions;
		List<Float> textureCoords;
		List<Float> normals;
		List<Uint> indices;

		while (std::getline(objfile, line))
		{
			List<String> split = SplitString(line, ' ');

			if (line.rfind("v ", 0) == 0)
			{
				positions.push_back(std::stof(split[1]));
				positions.push_back(std::stof(split[2]));
				positions.push_back(std::stof(split[3]));
			}

			if (line.rfind("vt ", 0) == 0)
			{
				t.push_back(Vec2(std::stof(split[1]), std::stof(split[2])));
			}

			if (line.rfind("vn ", 0) == 0)
			{
				n.push_back(Vec3(std::stof(split[1]), std::stof(split[2]), std::stof(split[3])));
			}

			if (line.rfind("f ", 0) == 0)
			{
				List<String> vertices(split.begin() + 1, split.end());

				if (vertices.size() == 4)
				{
					vertices = {
						vertices[0], vertices[1], vertices[2],
						vertices[2], vertices[3], vertices[0]
					};
				}

				for (Uint i = 0; i < vertices.size(); i++)
				{
					List<String> vertex = SplitString(vertices[i], '/');
					indices.push_back(std::abs(std::stoi(vertex[0])) - 1);
					if (vertex[1].size() > 0)
					{
						Int64 tci = std::abs(std::stoi(vertex[1]));
						Vec2 tc = t[tci - 1];
						textureCoords.push_back(tc.x);
						textureCoords.push_back(tc.y);
					}
					if (vertex[2].size() > 0)
					{
						Int64 noi = std::abs(std::stoi(vertex[2]));
						Vec3 no = n[noi - 1];
						normals.push_back(no.x);
						normals.push_back(no.y);
						normals.push_back(no.z);
					}
				}
			}
		}

		objfile.close();

		return new VertexData(positions, textureCoords, normals, indices);
	}
}