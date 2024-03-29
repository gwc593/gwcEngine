#pragma once

namespace gwcEngine
{
	enum class ShaderDataType
	{
		None = 0,
		Float,
		Vec2,
		Vec3,
		Vec4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool,
		Sampler2D
	};


	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type) {
		case ShaderDataType::None:   return 0;
		case ShaderDataType::Float: return 4;
		case ShaderDataType::Vec2: return 4*2;
		case ShaderDataType::Vec3: return 4*3;
		case ShaderDataType::Vec4: return 4*4;
		case ShaderDataType::Mat3:   return 4*3*3;
		case ShaderDataType::Mat4:   return 4*4*4;
		case ShaderDataType::Int:    return 4;
		case ShaderDataType::Int2:   return 4*2;
		case ShaderDataType::Int3:   return 4*3;
		case ShaderDataType::Int4:   return 4*4;
		case ShaderDataType::Bool:   return 1;
		}
		GE_CORE_ASSERT(false, "Unsupported Shader Data Type");
		return 0;
	}
	
	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Offset;
		uint32_t Size;
		bool Normalised;
		
		BufferElement()
		{
			m_Count = 0;
			Normalised = false;
			Offset = 0;
			Size = 0;
			Type = ShaderDataType::None;
			Name = "";
		}

		BufferElement(ShaderDataType type, const std::string& name, bool normalised = false) 
			:Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalised(normalised)
		{
			m_Count = 0;
		}

		uint32_t GetComponentCount() const 
		{ 
			switch (Type) {
				case ShaderDataType::None:   return 0;
				case ShaderDataType::Float: return 1;
				case ShaderDataType::Vec2: return 2;
				case ShaderDataType::Vec3: return 3;
				case ShaderDataType::Vec4: return 4;
				case ShaderDataType::Mat3:   return 3 * 3;
				case ShaderDataType::Mat4:   return 4 * 4;
				case ShaderDataType::Int:    return 1;
				case ShaderDataType::Int2:   return 2;
				case ShaderDataType::Int3:   return 3;
				case ShaderDataType::Int4:   return 4;
				case ShaderDataType::Bool:   return 1;
			}

			GE_CORE_ASSERT(false, "Unsupported Shader Data Type");
			return 0;
		}

	private:
		uint32_t m_Count;
	};

	class BufferLayout
	{
	public:
		BufferLayout(){}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
		:m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		inline uint32_t GetStride()const { return m_Stride; }

		inline std::vector<BufferElement> GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }

		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;

		void CalculateOffsetsAndStride()
		{			
			for (auto& element : m_Elements) {
				element.Offset = m_Stride;
				m_Stride += element.Size;
			}
		}
	};




}