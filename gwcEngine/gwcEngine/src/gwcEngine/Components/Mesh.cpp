#include "gepch.h"
#include "Mesh.h"

namespace gwcEngine
{

	Mesh::Mesh()
	{
		m_VB = nullptr;
		m_VA = nullptr;
		m_IB = nullptr;
		m_vertexData = nullptr;
		m_indexData = nullptr;
		m_vertexDataSize = 0;
		m_indexCount = 0;
		m_VA.reset(gwcEngine::VertexArray::Create());
	}

	Mesh::Mesh(const std::shared_ptr<VertexBuffer>& vb, std::shared_ptr<IndexBuffer>& ib)
	{
		m_VB = vb;
		m_IB = ib;

	}

	Mesh::Mesh(float* const& verts, std::size_t sizeV, BufferLayout layout, uint32_t* const& indicies, uint32_t sizeI)
	{

		m_vertexData = (float*)std::realloc(m_vertexData, sizeV);
		for (int i = 0; i < sizeV / sizeof(float); i++)
			m_vertexData[i] = verts[i];

		m_vertexDataSize = sizeV;


		m_indexData = (uint32_t*)std::realloc(m_indexData, sizeI * sizeof(uint32_t));

		m_indexCount = sizeI;

		for (int i = 0; i < sizeI; i++)
			m_indexData[i] = indicies[i];

		m_VB.reset(VertexBuffer::Create(m_vertexData, m_vertexDataSize));
		m_IB.reset(IndexBuffer::Create(m_indexData, m_indexCount));

		m_layout = layout;

		m_VB->SetLayout(m_layout);

	}

	void Mesh::SetVertexBuffer(float* const& verts,const uint32_t sizeV, BufferLayout layout)
	{
		m_vertexData = (float*)std::realloc(m_vertexData, sizeV);
		for (int i = 0; i < sizeV/sizeof(float); i++)
			m_vertexData[i] = verts[i];

		m_vertexDataSize = sizeV;

		m_VB.reset(VertexBuffer::Create(m_vertexData, m_vertexDataSize));
		
		m_layout = layout;
		m_VB->SetLayout(m_layout);


	}

	void Mesh::SetIndexBuffer(uint32_t* const& indicies, const uint32_t& sizeI)
	{
		m_indexData = (uint32_t*)std::realloc(m_indexData, sizeI *sizeof(uint32_t));

		m_indexCount = sizeI;

		for (int i = 0; i < sizeI; i++)
			m_indexData[i] = indicies[i];

		m_IB.reset(IndexBuffer::Create(m_indexData, m_indexCount));

	}

	void Mesh::InitVertexArray()
	{
		if (m_VB != nullptr && m_IB != nullptr) {
			m_VA->AddVertexBuffer(m_VB);
			m_VA->SetIndexBuffer(m_IB);
		}
	}

}