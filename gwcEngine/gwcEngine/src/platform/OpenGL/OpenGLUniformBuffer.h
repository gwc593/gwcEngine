#pragma once
#include"gwcEngine/Renderer/Shader/UniformBuffer.h"

namespace gwcEngine
{
	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer(const std::string& blockName);

		virtual void SyncData() const override;
		virtual void BindShader(Ref<Shader> shader) const override;
		virtual void UnbindShader() const override;
	private:
		uint32_t m_RendererID;
		mutable uint32_t m_BlockIndex;
		std::string m_BlockName;
	};
}
