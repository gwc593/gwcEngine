#pragma once

namespace gwcEngine
{
	enum class RendererAPI
	{
		None = 0,
		OpenGL,
		DirectX,
		Vulkan,
		Metal
	};
	class Renderer
	{

	public:
		inline static RendererAPI GetAPI() { return s_RendereAPI; }

	private:
		static RendererAPI s_RendereAPI;

	};
	
}