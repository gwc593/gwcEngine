#pragma once

#include "gwcEngine/Renderer/RendererAPI.h"

namespace gwcEngine
{
	class OpenGLRendererAPI : public RendererAPI
	{

	public:
		virtual void Clear() override;

		//todo - vect4 implimentation?
		virtual void SetClearColour() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}