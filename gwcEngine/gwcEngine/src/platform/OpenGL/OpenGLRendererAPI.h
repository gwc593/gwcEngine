#pragma once

#include "gwcEngine/Renderer/RendererAPI.h"

namespace gwcEngine
{
	class OpenGLRendererAPI : public RendererAPI
	{

	public:
		virtual void Clear() override;

		virtual void SetClearColour(const glm::vec4& colour) override;

		virtual void DrawTrisIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

		virtual void DrawLinesIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void SetVSync(bool state) override;

		virtual bool IsVsync() override;

	};
}