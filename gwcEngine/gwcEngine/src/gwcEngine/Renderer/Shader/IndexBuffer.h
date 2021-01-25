#pragma once
#include"Buffer.h"

namespace gwcEngine
{
	struct IndexData
	{
		std::vector<uint32_t> IndexOrder;
		uint32_t Count;
		bool IsDynamic;
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indicies, uint32_t count, bool isDynamic = false);

	protected:
		IndexData m_IndexData;
	};
}
