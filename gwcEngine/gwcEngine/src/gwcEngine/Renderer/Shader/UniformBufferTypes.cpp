#include "gepch.h"
#include"UniformBufferTypes.h"

namespace gwcEngine
{

	uint32_t GetSize(const UniformBufferTypes& type)
	{
		switch (type) {
		case UniformBufferTypes::None: GE_CORE_ASSERT(false, "invalid uniform buffer Element Type"); break;
		case UniformBufferTypes::Bool: return 4;
		case UniformBufferTypes::Int: return 4;
		case UniformBufferTypes::Float: return 4;
		case UniformBufferTypes::Vec2: return 8;
		case UniformBufferTypes::Vec3:return 16;
		case UniformBufferTypes::Vec4:return 16;
		case UniformBufferTypes::Mat3: return 3*16;
		case UniformBufferTypes::Mat4: return 4*16;

		default: GE_CORE_ASSERT(false, "Unsupported uniform buffer Element Type"); break;
		}
	}

	bool IsScalar(const UniformBufferTypes& type)
	{
		switch (type) {
		case UniformBufferTypes::None: GE_CORE_ASSERT(false, "invalid uniform buffer Element Type"); break;
		case UniformBufferTypes::Bool: return true;
		case UniformBufferTypes::Int: return true;
		case UniformBufferTypes::Float: return true;
		case UniformBufferTypes::Vec2: return false;
		case UniformBufferTypes::Vec3:return false;
		case UniformBufferTypes::Vec4:return false;
		case UniformBufferTypes::Mat3: return false;
		case UniformBufferTypes::Mat4: return false;

		default: GE_CORE_ASSERT(false, "Unsupported uniform buffer Element Type"); break;
		}
	}

	UniformBufferLayout::~UniformBufferLayout()
	{
		if (!m_Base)
			free(m_Base);
	}

	void  UniformBufferLayout::AddSpace(const UniformBufferTypes& elem)
	{
		while (m_Padding < GetSize(elem)) {
			auto temp = realloc(m_Base, size_t((m_Padding + m_Stride) + 16));
			if (!temp) {
				GE_CORE_FATAL("Unable to allocate memory");
				return;
			}
			m_Base = temp;
			m_Padding += 16;
		}
	}

	void  UniformBufferLayout::Set(const std::string& handle, void* data, uint32_t size)
	{
		if (m_Offset.find(handle) == m_Offset.end())
			GE_CORE_ERROR("handle not found");	
		memcpy((void*)(((char*)m_Base) + m_Offset[handle]), data, size);
	}

	void UniformBufferLayout::AddElement(const std::string& handle, const UniformBufferTypes& elem, uint32_t arrSize)
	{
		bool isArry = arrSize > 1;
		int i = 0;
		if (!m_Base) {
			m_Base = malloc(16);
			m_Padding = 16;
			m_Stride = 0;
		}
		for (; arrSize; --arrSize) {
			if (IsScalar(elem)) {

				AddSpace(elem);
				m_Offset[handle] = m_Stride;
				m_Stride += GetSize(elem);
				m_Padding -= GetSize(elem);
			}
			else {
				//reallign to vec4
				uint32_t addPad = m_Stride % 16;
				if (addPad) {
					m_Stride += 16-addPad;
					m_Padding -= 16-addPad;
				}

				AddSpace(elem);

				m_Offset[isArry?handle+"["+std::to_string(i++)+"]":handle] = m_Stride;
				m_Stride += GetSize(elem);
				m_Padding -= GetSize(elem);
			}
		}

		memset(m_Base, '\0', m_Stride + m_Padding);
	}


	void UniformBufferLayout::AddStructure(const std::string& handle, const UniformBufferLayout& structure, uint32_t arrSize)
	{
		bool isArry = arrSize > 1;
		int i = 0;
		if (!m_Base) {
			m_Base = malloc(16);
			m_Padding = 16;
			m_Stride = 0;
		}

		for (; arrSize; --arrSize) {
			//reallign to vec4
			uint32_t addPad = m_Stride % 16;
			if (addPad) {
				m_Stride += 16 - addPad;
				m_Padding -= 16 - addPad;
			}

			while (m_Padding < structure.Size()) {
				auto temp = realloc(m_Base, size_t((m_Padding + m_Stride) + 16));
				if (!temp) {
					GE_CORE_FATAL("Unable to allocate memory");
					return;
				}
				m_Base = temp;
				m_Padding += 16;
			}
			for (auto offset : structure.m_Offset) {
				m_Offset[isArry ? handle + "[" + std::to_string(i) + "]."+ offset.first : handle + "."+ offset.first] = m_Stride+offset.second;
			}
			++i;
			m_Stride += structure.Size();
			m_Padding -= structure.Size();
			
		}

		memset(m_Base, '\0', m_Stride + m_Padding);
	}
}
