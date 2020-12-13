#pragma once
#include "gwcEngine/Core/core.h"
namespace gwcEngine
{
	struct FrameBufferSpecification
	{
		uint32_t Width, Height;
		float NClip, FClip;
		uint32_t samples = 1;

		// this is required for rendering pipelines such as vulcan/metal where you need to explicitly declare your buffers for swapping. (rendering to the screen or not)
		bool SwapChainTarget = false;
	};
	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;

		virtual const FrameBufferSpecification& GetSpecification() const = 0;

		virtual bool Resize(uint32_t width, uint32_t height) = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void BindTexture() const = 0;
		virtual void UnbindTexture() const = 0;

		virtual void GetDepthData(uint32_t x, uint32_t y) = 0;

		virtual uint32_t GetColourAttachmentRendererID() const = 0;
		
		//Todo requild frambuffer based on spec change.
		//virtual FrameBufferSpecification& GetSpecification() = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSpecification& spec);

	private:

	};
}