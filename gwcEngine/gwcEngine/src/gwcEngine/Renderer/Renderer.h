#pragma once
#include "RendererAPI.h"
#include"RenderCommand.h"
#include"OrthographicCamera.h"
#include"PerspectiveCamera.h"
#include"Shader.h"



namespace gwcEngine
{
	class Renderer
	{

	public:

		static void BeginScene(OrthographicCamera& camera); //TODO - take in scene params, lights etc
		static void BeginScene(PerspectiveCamera& camera); //TODO - take in scene params, lights etc
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4 transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
	
}