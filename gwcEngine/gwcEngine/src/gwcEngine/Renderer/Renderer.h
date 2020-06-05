#pragma once
#include "RendererAPI.h"
#include"RenderCommand.h"
namespace gwcEngine
{
	class Renderer
	{

	public:

		static void BeginScene(); //TODO - take in scene params, lights etc
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:

	};
	
}