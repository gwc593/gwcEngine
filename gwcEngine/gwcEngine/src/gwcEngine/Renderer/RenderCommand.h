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

		inline static void SetClearColour(const glm::vec4& colour) 
		{
			s_RendererAPI->SetClearColour(colour);
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		inline static void DrawTrisIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawTrisIndexed(vertexArray);
		}

		inline static void DrawLinesIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawLinesIndexed(vertexArray);
		}

		inline static void SetVsync(bool state)
		{
			s_RendererAPI->SetVSync(state);
		}

		inline static bool IsVsync()
		{
			return s_RendererAPI->IsVsync();
		}

	private:
		static RendererAPI* s_RendererAPI;
	};
}