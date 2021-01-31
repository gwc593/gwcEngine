#pragma once
#include"Buffer.h"
#include "gwcEngine/Renderer/Shader/Shader.h"
#include "UniformBufferTypes.h"
namespace gwcEngine
{


	class UniformBuffer
	{
	public:
		virtual ~UniformBuffer() = default;
		static UniformBuffer* Create(const std::string& blockName);

		virtual void SyncData() const = 0;
		virtual void BindShader(Ref<Shader> shader) const  = 0;
		virtual void UnbindShader() const = 0;

		void AddElement(const std::string& handle, const UniformBufferTypes& elem, uint32_t arrSize = 1) { m_Layout.AddElement(handle, elem, arrSize); }
		void AddStructure(const std::string& handle, const UniformBufferLayout& structure, uint32_t arrSize = 1) { m_Layout.AddStructure(handle, structure, arrSize); }
		void Set(const std::string& handle, void* data, uint32_t size) { m_Layout.Set(handle, data, size); }

	protected:
		UniformBufferLayout m_Layout;
	};
}
