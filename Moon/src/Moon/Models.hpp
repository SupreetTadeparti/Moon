#pragma once

#include "Core.h"
#include "Model.hpp"

namespace Moon
{
	class Models
	{
	public:
		MOON_API static Model* Rect(Float width, Float height);
		MOON_API static Model* Rect(Material* material, Float width, Float height);
		MOON_API static Model* Rect(Shader* shader, Float width, Float height);
		MOON_API static Model* Rect(Shader* shader, Material* material, Float width, Float height);
		MOON_API static Model* Box(Float width, Float length, Float height);
		MOON_API static Model* Box(Material* color, Float width, Float length, Float height);
		MOON_API static Model* Box(Shader* shader, Float width, Float length, Float height);
		MOON_API static Model* Box(Shader* shader, Material* color, Float width, Float length, Float height);
	};
}
