#pragma once

#include "Core.h"
#include "Scene.hpp"

namespace Moon
{
	enum class MOON_API RenderType
	{
		TwoD, ThreeD
	};

	class Renderer
	{
	public:
		MOON_API static void Update();
		MOON_API static void Prepare();
		MOON_API static void Render();
		MOON_API static void RenderEntity(Entity* entity);
		MOON_API static inline Scene* GetScene() { return s_Scene; }
		MOON_API static inline RenderType GetRenderType() { return s_RenderType; }
		MOON_API static inline Double GetFOV() { return s_FOV; }
		MOON_API static inline void SetScene(Scene* scene) { s_Scene = scene; }
		MOON_API static inline void SetFOV(Double fov) { s_FOV = glm::radians(fov); }
		MOON_API static inline void SetRenderType(RenderType renderType) { s_RenderType = renderType; }
		MOON_API static inline void SetBackgroundColor(Vec3 color) { s_BackgroundColor = color / 255.0f; }
	private:
		static Scene* s_Scene;
		static Double s_FOV;
		static Vec3 s_BackgroundColor;
		static RenderType s_RenderType;
	};
}