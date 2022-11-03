#include "Sprite.hpp"

namespace Moon
{
	Sprite::Sprite(const String& textureFile)
	{
		s_Model = new Model(Shape::Rect);
		s_Model->SetMaterial(new Material(new Texture(textureFile)));
	}
}
