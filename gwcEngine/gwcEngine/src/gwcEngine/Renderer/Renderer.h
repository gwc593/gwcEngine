#pragma once
#include "RendererAPI.h"
#include"RenderCommand.h"
#include"Shader/Shader.h"
#include "gwcEngine/Components/Renderable/Material.h"


namespace gwcEngine
{
	class CameraBase;

	enum class RendType
	{
		none = 0,
		lines = 1,
		triangles = 2
	};

	class Renderer
	{

	public:

		static void BeginScene(); //TODO - take in scene params, lights etc

		static void SetActiveCamera(const Ref<CameraBase>& camera);
		static void SetViewProjection(const glm::mat4& vp);
		static void EndScene();
		
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f), RendType rType = RendType::triangles);
		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Material>& material, const glm::mat4& transform = glm::mat4(1.0f), RendType rType = RendType::triangles);



		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
	
}