#pragma once
#include "gwcEngine/Renderer/Shader/Buffer.h"
#include "gwcEngine/Renderer/Shader/Shader.h"
#include "gwcEngine/Renderer/Texture.h"

namespace gwcEngine
{
	class Shader;

	class ShaderUniform
	{
	public:
		static ShaderUniform* Create(const std::string& name, const ShaderDataType& type, Shader* shader);
		virtual ~ShaderUniform() = default;

		virtual std::string& GetName() { return m_name; }

		virtual void SetValue(const bool& value) { GE_WARN("Incompatible data type bool provided to {0}", this->m_name); }
		virtual void SetValue(const int& value) { GE_WARN("Incompatible data type int provided to {0}", this->m_name); }
		virtual void SetValue(const float& value) { GE_WARN("Incompatible data type float provided to {0}", this->m_name); }
		virtual void SetValue(const glm::vec2& value) { GE_WARN("Incompatible data type vec2 provided to {0}", this->m_name); }
		virtual void SetValue(const glm::vec3& value) { GE_WARN("Incompatible data type vec3 provided to {0}", this->m_name); }
		virtual void SetValue(const glm::vec4& value) { GE_WARN("Incompatible data type vec4 provided to {0}", this->m_name); }
		virtual void SetValue(const glm::mat3& value) { GE_WARN("Incompatible data type mat3 provided to {0}", this->m_name); }
		virtual void SetValue(const glm::mat4& value) { GE_WARN("Incompatible data type mat3 provided to {0}", this->m_name); }
		virtual void SetValue(const Ref<Texture2D>& value) { GE_WARN("Incompatible data type Texture2D provided to {0}", this->m_name); }

	protected:
		std::string m_name;
	};
}