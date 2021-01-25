#include "gepch.h"
#include<glad/glad.h>
#include "OpenGLIndexBuffer.h"

namespace gwcEngine
{

	////////////////////////////////////
	//OpenGL index buffer implimenation
	////////////////////////////////////
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count, bool isDynamic) :
		m_count(count)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, (isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
}
