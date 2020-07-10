#pragma once
#include"gwcEngine/Renderer/Shader/Buffer.h"

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

		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		virtual const BufferLayout& GetLayout() const override {return m_Layout;}

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	////////////////////////////////////
	//OpenGL index buffer declaration
	////////////////////////////////////

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* verticies, uint32_t count, bool isDynamic = false);

		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const override { return m_count; }

	private:
		uint32_t m_RendererID;
		uint32_t m_count;
	};
}