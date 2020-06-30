#pragma once

#include"gwcEngine/Renderer/Shader/VertexArray.h"
#include <glm/glm.hpp>

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
		virtual void SetClearColour(const glm::vec4& colour) = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		virtual void SetVSync(bool state) = 0;
		virtual bool IsVsync() = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}