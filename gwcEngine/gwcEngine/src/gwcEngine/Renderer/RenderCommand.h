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
		inline static void SetClearColour() 
		{
			s_RendererAPI->SetClearColour();
		}


		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}