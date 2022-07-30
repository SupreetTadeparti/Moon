#pragma once

#include "Models.hpp"
#include "EventController.hpp"

namespace Moon
{
	class Sprite : public CallbackEventController
	{
	public:
		MOON_API Sprite(const String& textureFile);
		MOON_API inline Model* const GetModel() const { return s_Model; }
	private:
		Model* s_Model;
	};
}