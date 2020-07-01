#pragma once
#include "gwcEngine/Renderer/FrameBuffer.h"
namespace gwcEngine
{

	class OpenGLFrameBuffer: public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& spec);

		~OpenGLFrameBuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		const FrameBufferSpecification& GetSpecification() const override;

		virtual uint32_t GetColourAttachmentRendererID() const override { return m_ColourAttachment; }

	private:
		uint32_t m_RendererID;
		uint32_t m_ColourAttachment;
		uint32_t m_DepthBufferAttachment;
		FrameBufferSpecification m_Specification;
	};
}