#include"gepch.h"
#include<glad/glad.h>
#include"OpenGLVertexBuffer.h"

namespace gwcEngine
{
/////////////////////////////////////
//OpenGL vertex buffer implimenation
/////////////////////////////////////
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* verticies, uint32_t size)
	{
		//StoreVertexData(verticies, size);
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
}
