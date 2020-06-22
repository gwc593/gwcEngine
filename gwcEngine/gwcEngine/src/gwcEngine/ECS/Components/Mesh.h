#pragma once
#include"gwcEngine/ECS/ECS.h"
#include"gwcEngine/Renderer/Shader/VertexArray.h"

namespace gwcEngine 
{
	class Mesh 
	{
	public:
		Mesh();
		Mesh(int i);

		Mesh(const std::shared_ptr<VertexBuffer>& vb, std::shared_ptr<IndexBuffer>& ib);
		Mesh(float* const& verts, std::size_t sizeV, BufferLayout layout, uint32_t* const& indicies, uint32_t sizeI);

		inline std::shared_ptr<VertexBuffer> GetVertexBuffer() const { return m_VB; }
		inline std::shared_ptr<IndexBuffer> GetIndexBuffer() const { return m_IB; }
		inline std::shared_ptr<VertexArray> GetVertexArray() const { return m_VA; }

		void SetVertexBuffer(float* const& verts, uint32_t sizeV, BufferLayout layout);

		void SetIndexBuffer(uint32_t* const& indicies, const uint32_t& sizeI);

		void InitVertexArray();

	private:
		std::shared_ptr<VertexBuffer> m_VB;
		std::shared_ptr<IndexBuffer> m_IB;
		std::shared_ptr<VertexArray> m_VA;

	private:
		//void InitVertexArray();
	};

}


