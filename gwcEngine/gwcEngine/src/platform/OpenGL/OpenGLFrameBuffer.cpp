#include "gepch.h"
#include "OpenGLFrameBuffer.h"

#include<glad/glad.h>
namespace gwcEngine
{


	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& spec) 
		:m_Specification(spec)
	{
		Invalidate();
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
	}

	void OpenGLFrameBuffer::Invalidate()
	{

		//create colour attachment
		glCreateFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColourAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColourAttachment);

		//   todo   make an option
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColourAttachment, 0);

		//create depth attachment
		glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthBufferAttachment);
		glBindTexture(GL_TEXTURE_2D, m_DepthBufferAttachment);

		//todo higher precision depth buffer.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH32F_STENCIL8, m_Specification.Width, m_Specification.Height, 0, 
			GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);


		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthBufferAttachment, 0);

		GE_CORE_ASSERT((glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE), "Frame buffer not complete");
			
		//glDepthRange(m_Specification.NClip, m_Specification.FClip);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	bool OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height)
	{
		//update spec
		m_Specification.Height = height;
		m_Specification.Width = width;

		//resize colour buffer
		glBindTexture(GL_TEXTURE_2D, m_ColourAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		//resize depth buffer
		glBindTexture(GL_TEXTURE_2D, m_DepthBufferAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height, 0,
					 GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

		GE_CORE_ASSERT((glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE), "Frame buffer not complete");

		return false;
	}

	const gwcEngine::FrameBufferSpecification& OpenGLFrameBuffer::GetSpecification() const
	{
		return m_Specification;
	}

	void OpenGLFrameBuffer::Bind()
	{
		glViewport(0, 0, m_Specification.Width, m_Specification.Height);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	}

	void OpenGLFrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::BindTexture() const
	{
		glBindTexture(GL_TEXTURE_2D, m_ColourAttachment);
	}

	void OpenGLFrameBuffer::UnbindTexture() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	uint8_t OpenGLFrameBuffer::GetDepthData(uint32_t x, uint32_t y) const
	{
		if (x > m_Specification.Width || y > m_Specification.Height)
			return 255;

		glViewport(0, 0, m_Specification.Width, m_Specification.Height);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		uint8_t data;
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, &data);
		
		return data;
	}
}