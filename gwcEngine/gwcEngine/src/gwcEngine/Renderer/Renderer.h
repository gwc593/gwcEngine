#pragma once
#include "RendererAPI.h"
#include"RenderCommand.h"
#include"Shader/Shader.h"
#include "Material.h"


namespace gwcEngine
{
	class CameraBase;
	class Renderer
	{

	public:

		static void BeginScene(const Ref<CameraBase>& camera); //TODO - take in scene params, lights etc

		static void SetActiveCamera(const Ref<CameraBase>& camera);
		static void SetViewProjection(const glm::mat4& vp);
		static void EndScene();
		
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));
		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Material>& material, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
	
}