#pragma once
#include"RendererAPI.h"
namespace gwcEngine
{
	class RenderCommand
	{
	public:
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		};

		//todo - vect4 implimentation?
		inline static void SetClearColour(const glm::vec4& colour) 
		{
			s_RendererAPI->SetClearColour(colour);
		}


		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}