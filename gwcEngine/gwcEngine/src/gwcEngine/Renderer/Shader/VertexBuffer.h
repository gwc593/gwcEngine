#pragma once
#include "Buffer.h"

namespace gwcEngine 
{
	struct VertexData
	{
		std::vector<float> Vertecies;
		uint32_t Size;
		BufferLayout Layout;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* verticies, uint32_t size);

	protected:
		void StoreVertexData(float* verticies, uint32_t size);
		VertexData m_VertexBufferData;
	};

}
