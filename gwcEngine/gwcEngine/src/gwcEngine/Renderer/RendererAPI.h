#pragma once

#include"gwcEngine/Renderer/VertexArray.h"

namespace gwcEngine
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL,
			DirectX,
			Vulkan,
			Metal
		};

	public:
		virtual void Clear() = 0;

		//todo - vect4 implimentation?
		virtual void SetClearColour() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}