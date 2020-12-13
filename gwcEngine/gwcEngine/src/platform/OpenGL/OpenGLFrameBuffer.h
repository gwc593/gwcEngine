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

		bool Resize(uint32_t width, uint32_t height) override;

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void BindTexture() const override;
		virtual void UnbindTexture() const override;
		virtual void GetDepthData(uint32_t x, uint32_t y) override;

		const FrameBufferSpecification& GetSpecification() const override;

		virtual uint32_t GetColourAttachmentRendererID() const override { return m_ColourAttachment; }

	private:
		uint32_t m_RendererID;
		uint32_t m_ColourAttachment;
		uint32_t m_DepthBufferAttachment;
		FrameBufferSpecification m_Specification;
	};
}