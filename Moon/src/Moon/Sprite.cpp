#include "Sprite.hpp"

namespace Moon
{
	Sprite::Sprite(const String& textureFile)
	{
		Texture* texture = new Texture(textureFile);
		Material* material = new Material(texture);
		Shader* shader = Shader::GenerateDefaultTexture();
		s_Model = Models::Rect(shader, material, texture->GetWidth(), texture->GetHeight());
	}
}
