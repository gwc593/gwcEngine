#include"gepch.h"
#include<glad/glad.h>
#include"OpenGLUniformBuffer.h"
#include "OpenGLShader.h"

namespace gwcEngine 
{
	OpenGLUniformBuffer::OpenGLUniformBuffer(const std::string& blockName)
	{
		m_BlockName = blockName;

		glCreateBuffers(1, &m_RendererID);
	}

	void OpenGLUniformBuffer::SyncData() const
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
		glBufferData(GL_UNIFORM_BUFFER, m_Layout.Size(), m_Layout.GetData(), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void OpenGLUniformBuffer::BindShader(Ref<Shader> shader) const
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);

		auto glShader = std::dynamic_pointer_cast<OpenGLShader>(shader);

		m_BlockIndex = glGetUniformBlockIndex(glShader->m_Renderer_ID, m_BlockName.c_str());


		if (m_BlockIndex == GL_INVALID_INDEX) {
			GE_TRACE("oops");
			return;
		}

		int size;
		glGetActiveUniformBlockiv(glShader->m_Renderer_ID, m_BlockIndex,  GL_UNIFORM_BLOCK_DATA_SIZE, &size);

		if (size != m_Layout.Size()) {
			GE_CORE_ERROR("uniform buffer size {0} bytes != uniform block size on shader of {1} bytes, incorrect format", m_Layout.Size(), size);
			return;
		}

		glBindBufferBase(GL_UNIFORM_BUFFER, m_BlockIndex, m_RendererID);
	}

	void OpenGLUniformBuffer::UnbindShader() const
	{
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}
