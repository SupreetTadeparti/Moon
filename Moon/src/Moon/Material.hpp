#pragma once

#include "Core.h"

namespace Moon
{
	enum class MaterialType
	{
		Texture,
		Color
	};

	class MOON_API Texture
	{
	public:
		Texture(const String& texturePath);
		Texture(Uint textureID);
		~Texture();
		void Bind(Uint slot = 0) const;
		void Unbind() const;
		inline Uint GetWidth() const { return m_Width; }
		inline Uint GetHeight() const { return m_Height; }
	private:
		Uint m_TextureID;
		Uint m_Width;
		Uint m_Height;
	};

	class Color
	{
	public:
		MOON_API Color(Vec4 color);
		MOON_API Color(Float r, Float g, Float b, Float a = 1.0);

		MOON_API inline Vec4 GetColor() const { return m_Color; }
	private:
		Vec4 m_Color;
	};

	class Material
	{
	public:
		MOON_API Material(Texture* texture);
		MOON_API Material(Color* color);

		MOON_API inline Texture* GetTexture() const { return m_Texture; }
		MOON_API inline Color* GetColor() const { return m_Color; }
		MOON_API inline MaterialType GetMaterialType() const { return m_MaterialType; }

		MOON_API static Material* GetDefault();
	private:
		static void GenerateDefault();

		MaterialType m_MaterialType;
		Texture* m_Texture;
		Color* m_Color;

		static Material* s_DefaultMaterial;
		static const Vec4 s_DefaultColor;
	};
}