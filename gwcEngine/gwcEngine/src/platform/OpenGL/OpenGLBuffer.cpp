#include"gepch.h"
#include"OpenGLBuffer.h"

#include<glad/glad.h>

namespace gwcEngine
{
	/////////////////////////////////////
	//OpenGL vertex buffer implimenation
	/////////////////////////////////////
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* verticies, uint32_t size)
	{
		glCreateBuffers(1, &m_RendererID);
<<<<<<< HEAD
		Bind();
=======
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
>>>>>>> 1d48859dafbe6d5ac6a6c01556f3a8669b9decb3
		glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);
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


	////////////////////////////////////
	//OpenGL index buffer implimenation
	////////////////////////////////////
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count):
		m_count(count)
	{
		glCreateBuffers(1, &m_RendererID);
<<<<<<< HEAD
		Bind();
=======
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
>>>>>>> 1d48859dafbe6d5ac6a6c01556f3a8669b9decb3
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(uint32_t), indices, GL_STATIC_DRAW);
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