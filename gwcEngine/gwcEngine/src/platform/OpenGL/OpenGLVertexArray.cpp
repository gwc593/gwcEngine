#include"gepch.h"
#include"OpenGLVertexArray.h"

#include<glad/glad.h>

namespace gwcEngine
{

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type) {
		case ShaderDataType::Float: return GL_FLOAT;
		case ShaderDataType::Vec2: return GL_FLOAT;
		case ShaderDataType::Vec3: return GL_FLOAT;
		case ShaderDataType::Vec4: return GL_FLOAT;
		case ShaderDataType::Mat3:   return GL_FLOAT_MAT3; //should this just be GL_FLOAT
		case ShaderDataType::Mat4:   return GL_FLOAT_MAT4; ////should this just be GL_FLOAT
		case ShaderDataType::Int:    return GL_INT;
		case ShaderDataType::Int2:   return GL_INT;
		case ShaderDataType::Int3:   return GL_INT;
		case ShaderDataType::Int4:   return GL_INT;
		case ShaderDataType::Bool:   return GL_BOOL;
		}

		GE_CORE_ASSERT(false, "unsupported ShaderDataType");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1,&m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		Bind();
		GE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout defined...");

		vertexBuffer->Bind();


		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();

		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
								  element.GetComponentCount(),
								  ShaderDataTypeToOpenGLBaseType(element.Type),
								  element.Normalised ? GL_TRUE : GL_FALSE,
								  layout.GetStride(),
								  (const void*)element.Offset);
			++index;
		}

		m_VertexBuffers.push_back(vertexBuffer);

		Unbind();
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		Bind();
		//glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
		Unbind();
	}
}