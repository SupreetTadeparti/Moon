#pragma once

#include "Core.h"
#include "Text.hpp"

namespace Moon
{
	class Renderer
	{
	public:
		static MOON_API void AddEntity(Entity* entity);
		static MOON_API void AddText(Text* text);
		static MOON_API void Prepare();
		static MOON_API void Render();
		static MOON_API inline void SetBackgroundColor(Vec3 color) { s_BackgroundColor = color; };
	private:
		static std::unordered_map<Model*, std::vector<Entity*>> s_ModelEntityMap;
		static Vec3 s_BackgroundColor;
	};
}