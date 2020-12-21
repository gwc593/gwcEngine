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

	Mesh::Mesh(Mesh&& other) noexcept
	{
		this->m_IB = std::move(other.m_IB);
		this->m_VB = std::move(other.m_VB);
		this->m_VA = std::move(other.m_VA);
	}

	Mesh& Mesh::operator=(Mesh&& other) noexcept
	{
		if (&other == this)
			return *this;

		m_IB = std::move(other.m_IB);
		m_VB = std::move(other.m_VB);
		m_VA = std::move(other.m_VA);

		return *this;
	}

	Mesh::Mesh(const Mesh& other)
	{
		this->m_IB = other.m_IB;
		this->m_VB = other.m_VB;
		this->m_VA = other.m_VA;
	}


	Mesh& Mesh::operator=(const Mesh& other) 
	{
		if (&other == this)
			return *this;

		m_IB = other.m_IB;
		m_VB = other.m_VB;
		m_VA = other.m_VA;

		return *this;
	}

	Mesh::Mesh(const std::shared_ptr<VertexBuffer>& vb, std::shared_ptr<IndexBuffer>& ib)
	{
		m_VB = vb;
		m_IB = ib;
		InitVertexArray();
	}

	Mesh::Mesh(float* const& verts, std::size_t sizeV, BufferLayout layout, uint32_t* const& indicies, uint32_t sizeI, bool isDynamic)
	{
		m_VB.reset(VertexBuffer::Create(verts, (uint32_t)sizeV));
		m_VB->SetLayout(layout);

		m_IB.reset(IndexBuffer::Create(indicies, sizeI, isDynamic));
		InitVertexArray();

	}

	void Mesh::SetVertexBuffer(float* const& verts, const uint32_t sizeV, BufferLayout layout)
	{
		m_VB.reset(VertexBuffer::Create(verts, sizeV));
		m_VB->SetLayout(layout);
		InitVertexArray();
	}

	void Mesh::SetIndexBuffer(uint32_t* const& indicies, const uint32_t& sizeI, bool isDynamic)
	{

		m_IB.reset(IndexBuffer::Create(indicies, sizeI, isDynamic));
		InitVertexArray();

	}

	void Mesh::InitVertexArray()
	{
		if (m_VB != nullptr && m_IB != nullptr) {
			m_VA->AddVertexBuffer(m_VB);
			m_VA->SetIndexBuffer(m_IB);
		}
	}

	Ref<Mesh> Mesh::s_Quad = nullptr;

	Mesh Mesh::Quad()
	{
		if (s_Quad == nullptr) {
			
			s_Quad = CreateRef<Mesh>();

			gwcEngine::BufferLayout layout = {
			{gwcEngine::ShaderDataType::Float3, "a_Position"},
			{gwcEngine::ShaderDataType::Float2, "a_TexCoord"},
			{gwcEngine::ShaderDataType::Float3, "a_Normal"}
			};

			float left = -0.5f;
			float right = 0.5f;
			float bottom = -0.5f;
			float top = 0.5f;

			float verticesQuad[4 * 8] = {
				// ----Position---------// -- Text Cord-|---- Normals -----| 
					right, top,    0.0f,    1.0f, 1.0f,    0.0f, 0.0f,1.0f,
					right, bottom, 0.0f,    1.0f, 0.0f,    0.0f, 0.0f,1.0f,
					left,  bottom, 0.0f,    0.0f, 0.0f,    0.0f, 0.0f,1.0f,
					left,  top,    0.0f,    0.0f, 1.0f,    0.0f, 0.0f,1.0f
			};

			//f   t   v
			uint32_t indicesQuad[1 * 2 * 3] = {
				0,1,2,
				0,2,3,
			};

			s_Quad->SetVertexBuffer(verticesQuad, sizeof(verticesQuad), layout);
			s_Quad->SetIndexBuffer(indicesQuad, sizeof(indicesQuad) / sizeof(uint32_t), true);
		}

		return *s_Quad;
	}

	Ref<Mesh> Mesh::s_Cube = nullptr;

	Mesh Mesh::Cube()
	{
		if (s_Cube == nullptr) {

			s_Cube = CreateRef<Mesh>();

			gwcEngine::BufferLayout layout = {
			{gwcEngine::ShaderDataType::Float3, "a_Position"},
			{gwcEngine::ShaderDataType::Float2, "a_TexCoord"},
			{gwcEngine::ShaderDataType::Float3, "a_Normal"}
			};


			float vertices[3*12*8] = {
				// ------------Position---------// -- Text Cord--------|-------- Normals ------------| 

			   -0.500000f,  0.500000f,  0.500000f, 0.625000f, 0.000000f, -1.0000f, 0.0000f, 0.0000f,
			   -0.500000f, -0.500000f, -0.500000f, 0.375000f, 0.250000f, -1.0000f, 0.0000f, 0.0000f,
			   -0.500000f, -0.500000f,  0.500000f, 0.375000f, 0.000000f, -1.0000f, 0.0000f, 0.0000f,

			   -0.500000f,  0.500000f, -0.500000f, 0.625000f, 0.250000f, 0.0000f, 0.0000f, -1.0000f,
			    0.500000f, -0.500000f, -0.500000f, 0.375000f, 0.500000f, 0.0000f, 0.0000f, -1.0000f,
			   -0.500000f, -0.500000f, -0.500000f, 0.375000f, 0.250000f, 0.0000f, 0.0000f, -1.0000f,

				0.500000f,  0.500000f,  -0.500000f, 0.625000f, 0.500000f, 1.0000f, 0.0000f, 0.0000f,
				0.500000f, -0.500000f,   0.500000f, 0.375000f, 0.750000f, 1.0000f, 0.0000f, 0.0000f,
				0.500000f, -0.500000f,  -0.500000f, 0.375000f, 0.500000f, 1.0000f, 0.0000f, 0.0000f,

				0.500000f,  0.500000f,  0.500000f, 0.625000f, 0.750000f, 0.0000f, 0.0000f, 1.0000f,
			   -0.500000f, -0.500000f,  0.500000f, 0.375000f, 1.000000f, 0.0000f, 0.0000f, 1.0000f,
				0.500000f, -0.500000f,  0.500000f, 0.375000f, 0.750000f, 0.0000f, 0.0000f, 1.0000f,

			    0.500000f, -0.500000f, -0.500000f, 0.375000f, 0.500000f, 0.0000f, -1.0000f, 0.0000f,
			   -0.500000f, -0.500000f,  0.500000f, 0.125000f, 0.750000f, 0.0000f, -1.0000f, 0.0000f,
			   -0.500000f, -0.500000f, -0.500000f, 0.125000f, 0.500000f, 0.0000f, -1.0000f, 0.0000f,

			   -0.500000f, 0.500000f,  -0.500000f, 0.875000f, 0.500000f, 0.0000f, 1.0000f, 0.0000f,
				0.500000f, 0.500000f,   0.500000f, 0.625000f, 0.750000f, 0.0000f, 1.0000f, 0.0000f,
				0.500000f, 0.500000f,  -0.500000f, 0.625000f, 0.500000f, 0.0000f, 1.0000f, 0.0000f,

			   -0.500000f,  0.500000f,  0.500000f, 0.625000f, 0.000000f, -1.0000f, 0.0000f, 0.0000f,
			   -0.500000f,  0.500000f, -0.500000f, 0.625000f, 0.250000f, -1.0000f, 0.0000f, 0.0000f,
			   -0.500000f, -0.500000f, -0.500000f, 0.375000f, 0.250000f, -1.0000f, 0.0000f, 0.0000f,

			   -0.500000f,  0.500000f, -0.500000f, 0.625000f, 0.250000f, 0.0000f, 0.0000f, -1.0000f,
			    0.500000f,  0.500000f, -0.500000f, 0.625000f, 0.500000f, 0.0000f, 0.0000f, -1.0000f,
			    0.500000f, -0.500000f, -0.500000f, 0.375000f, 0.500000f, 0.0000f, 0.0000f, -1.0000f,

				0.500000f,  0.500000f, -0.500000f, 0.625000f, 0.500000f, 1.0000f, 0.0000f, 0.0000f,
				0.500000f,  0.500000f,  0.500000f, 0.625000f, 0.750000f, 1.0000f, 0.0000f, 0.0000f, 
			   -0.500000f, -0.500000f, -0.500000f, 0.375000f, 0.750000f, 1.0000f, 0.0000f, 0.0000f,

			    0.500000f,  0.500000f,  0.500000f, 0.625000f, 0.750000f, 0.0000f, 0.0000f, 1.0000f,
			   -0.500000f,  0.500000f,  0.500000f, 0.625000f, 1.000000f, 0.0000f, 0.0000f, 1.0000f,
			   -0.500000f, -0.500000f,  0.500000f, 0.375000f, 1.000000f, 0.0000f, 0.0000f, 1.0000f,

			    0.500000f, -0.500000f, -0.500000f, 0.375000f, 0.500000f, 0.0000f, -1.0000f, 0.0000f,
			    0.500000f, -0.500000f,  0.500000f, 0.375000f, 0.750000f,  0.0000f, -1.0000f, 0.0000f,
			   -0.500000f, -0.500000f,  0.500000f, 0.125000f, 0.750000f, 0.0000f, -1.0000f, 0.0000,

			   -0.500000f,  0.500000f, -0.500000f, 0.875000f, 0.500000f, 0.0000f, 1.0000f, 0.0000f,
			   -0.500000f,  0.500000f,  0.500000f, 0.875000f, 0.750000f,  0.0000f, 1.0000f, 0.0000f,
			    0.500000f,  0.500000f,  0.500000f, 0.625000f, 0.750000f,  0.0000f, 1.0000f, 0.0000
			};

			//f   t   v
			uint32_t indices[3*6*2] = {
				0,1,2,
				3,4,5,
				6,7,8,
				9,10,11,
				12,13,14,
				15,16,17,
				18,19,20,
				21,22,23,
				24,25,26,
				27,28,29,
				30,31,32,
				33,34,35,

			};

			s_Cube->SetVertexBuffer(vertices, sizeof(vertices), layout);
			s_Cube->SetIndexBuffer(indices, sizeof(indices) / sizeof(uint32_t), true);
		}

		return *s_Cube;
	}
}