#pragma once
#include"gwcEngine/Renderer/Shader/VertexBuffer.h"

namespace gwcEngine 
{
	/////////////////////////////////////
	//OpenGL vertex buffer Declaration
	/////////////////////////////////////
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* verticies, uint32_t size);

		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetLayout(const BufferLayout& layout) override { m_VertexBufferData.Layout = layout; }
		virtual const BufferLayout& GetLayout() const override { return m_VertexBufferData.Layout; }

	private:
		uint32_t m_RendererID;
	};
}
