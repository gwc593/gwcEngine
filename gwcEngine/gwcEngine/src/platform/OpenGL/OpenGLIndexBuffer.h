#pragma once
#include"gwcEngine/Renderer/Shader/IndexBuffer.h"
////////////////////////////////////
//OpenGL index buffer declaration
////////////////////////////////////
namespace gwcEngine
{

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