#pragma once

#include "gwcEngine/Renderer/RendererAPI.h"

namespace gwcEngine
{
	class OpenGLRendererAPI : public RendererAPI
	{

	public:
		virtual void Clear() override;

		virtual void SetClearColour(const glm::vec4& colour) override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}