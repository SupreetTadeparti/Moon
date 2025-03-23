#pragma once

#include "Core.h"

namespace Moon
{
	enum class MOON_API GeometryType
	{
		Rect, Box, Sphere
	};

	struct VertexData
	{
		List<Float> Positions;
		List<Float> TextureCoords;
		List<Float> Normals;
		List<Uint> Indices;

		VertexData(List<Float> positions = {}, List<Float> textureCoords = {}, List<Float> normals = {}, List<Uint> indices = {});
	};

	class Geometry
	{
	public:
		MOON_API static void Init(); // Generates vertices for default shapes
		MOON_API Geometry(GeometryType shape); // Default Shape
		MOON_API Geometry(const String& path); // Model Loading
		MOON_API inline VertexData* GetVertexData() const { return m_VertexData; }
	private:
		static List<String> SplitString(const String& string, Char delimeter);
		static VertexData* LoadOBJ(const String& path);
		static HashMap<GeometryType, VertexData*> s_DefaultVertexData;
		VertexData* m_VertexData;
	};
}

