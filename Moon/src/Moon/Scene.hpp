#pragma once

#include "Core.h"
#include "Text.hpp"
#include "CameraController.hpp"
#include "EventController.hpp"
#include "Light.hpp"

namespace Moon
{
	/* Draw Elements Indirect Command */
	/* Each RenderModel is associated with a model/geometry with which and entity is tring to be rendered with */
	struct RenderModel
	{
		Uint Count;			// Number of indices in geometry
		Uint InstanceCount; // Number of instances of model to be rendered
		Uint FirstIndex;	// Number of indices rendered prior to this model
		Uint BaseVertex;	// Number of vertices (non-repetitive) rendered prior to this model
		Uint BaseInstance;	// Number of instances rendered prior to this model
	};

	class Scene : public CallbackEventController
	{
	public:
		MOON_API Scene();
		MOON_API ~Scene();
		MOON_API void Render();
		MOON_API void AddModel(Model* model); // Updates vertex arrays and buffers with model data
		MOON_API void UpdateEntities(); // Updates entity data
		MOON_API void InitVertexData(); // Initializes vertex arrays and buffers with model data
		MOON_API void AddText(Text* entity);
		MOON_API void AddEntity(Entity* entity);
		MOON_API void RemoveEntity(Entity* entity);
		MOON_API void AddModelVertexData(Model* model); // Updates vertex data with model data
		MOON_API inline List<Model*>& GetModels() { return m_Models; }
		MOON_API inline List<Entity*>& GetEntities() { return m_Entities; }
		MOON_API inline Camera* GetCamera() const { return m_Camera; }
		MOON_API inline void SetCamera(Camera* camera) { m_Camera = camera; }
		MOON_API inline void SetCameraController(CameraController* cc);
		MOON_API inline SpotLight* GetSpotLight() const { return m_SpotLight; };
		MOON_API inline void SetSpotLight(SpotLight* light) { m_SpotLight = light; };
		MOON_API inline AmbientLight* GetAmbientLight() const { return m_AmbientLight; };
		MOON_API inline void SetAmbientLight(AmbientLight* light) { m_AmbientLight = light; };
		MOON_API inline DirectionalLight* GetDirectionalLight() const { return m_DirectionalLight; };
		MOON_API inline void SetDirectionalLight(DirectionalLight* light) { m_DirectionalLight = light; };
	private:
		VertexArray* m_VertexArray;
		List<VertexBuffer*> m_VertexBuffers;
		Buffer* m_VertexDataBuffer;
		Buffer* m_IndexBuffer;
		Bool m_EntityAdded; // Entity added flag for updating transformation/indirect buffers
		Bool m_First; // First time rendering flag for setting up vertex arrays/buffers
		Uint m_FirstIndex; // Total number of indices to be rendered
		Uint m_BaseVertex; // Total number of vertices to be rendered
		Uint m_BaseInstance; // Total number of instances to be rendered
		Buffer* m_IndirectBuffer; // Stores m_Indirect data in buffer format
		Buffer* m_TransformationBuffer; // Stores m_Transformations data in buffer format
		ShaderStorageBuffer* m_ShaderStorageBuffer; // Stores material data in SSO format
		Camera* m_Camera;
		Shader* m_Shader;
		AmbientLight* m_AmbientLight;
		DirectionalLight* m_DirectionalLight;
		SpotLight* m_SpotLight;
		List<Model*> m_Models;
		List<Entity*> m_Entities;
		List<Mat4> m_Transformations;
		HashMap<Model*, Int> m_IndirectIndices; // Maps models to their index in m_Indirect
		List<RenderModel> m_Indirect; // List of draw commands for indirect rendering
	};
}