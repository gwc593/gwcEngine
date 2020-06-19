#include "gepch.h"
#include "Mesh.h"

#include "gwcEngine/Renderer/Renderer.h"

namespace gwcEngine
{

	Mesh::Mesh()
	{
		m_VB = nullptr;
		m_VA = nullptr;
		m_IB = nullptr;

		m_VA.reset(gwcEngine::VertexArray::Create());
	}

	Mesh::Mesh(const std::shared_ptr<VertexBuffer>& vb, std::shared_ptr<IndexBuffer>& ib)
	{
		m_VB = vb;
		m_IB = ib;
		InitVertexArray();
	}

	Mesh::Mesh(float* const& verts, std::size_t sizeV, BufferLayout layout, uint32_t* const& indicies, uint32_t sizeI)
	{
		m_VB.reset(VertexBuffer::Create(verts, (uint32_t)sizeV));
		m_VB->SetLayout(layout);

		m_IB.reset(IndexBuffer::Create(indicies, sizeI));
		InitVertexArray();

	}

	void Mesh::SetVertexBuffer(float* const& verts, const uint32_t sizeV, BufferLayout layout)
	{
		m_VB.reset(VertexBuffer::Create(verts, sizeV));
		m_VB->SetLayout(layout);
		InitVertexArray();
	}

	void Mesh::SetIndexBuffer(uint32_t* const& indicies, const uint32_t& sizeI)
	{

		m_IB.reset(IndexBuffer::Create(indicies, sizeI));
		InitVertexArray();

	}

	void Mesh::InitVertexArray()
	{
		if (m_VB != nullptr && m_IB != nullptr) {
			m_VA->AddVertexBuffer(m_VB);
			m_VA->SetIndexBuffer(m_IB);
		}
	}

}