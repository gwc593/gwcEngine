#pragma once

namespace gwcEngine
{

	enum class UniformBufferTypes
	{
		None = 0,
		Bool,
		Int,
		Float,
		Vec2,
		Vec3,
		Vec4,
		Mat3,
		Mat4
	};

	class UniformBufferLayout;
	using UniformBufferStruct = gwcEngine::UniformBufferLayout;

	class UniformBufferLayout
	{
	public:
		UniformBufferLayout() = default;
		~UniformBufferLayout();

		void AddElement(const std::string& handle, const UniformBufferTypes& elem, uint32_t arrSize = 1);
		void AddStructure(const std::string& handle, const UniformBufferLayout& structure, uint32_t arrSize = 1);
		void Set(const std::string& handle, void* data, uint32_t size);


		const uint32_t Size()const {return m_Stride+m_Padding;}

		const uint32_t GetStride() const { return m_Stride; }

		const void* GetData() const { return m_Base; }

	protected:
		void* m_Base = nullptr;
		bool m_EndIsScalar = true;
		uint32_t m_Padding = 0;
		uint32_t m_Stride = 0;
		uint32_t m_NextPos = 0;

		std::vector<UniformBufferTypes> m_Layout;

		std::map<std::string, intptr_t> m_Offset;

	private:
		void AddSpace(const UniformBufferTypes& elem);
	};

}
