#pragma once
#include "gwcEngine/Core/core.h"
#include<string>
namespace gwcEngine
{
	//todo Texture manager with slots to asset mapping
	class Texture
	{
	public:
		virtual ~Texture() = default;
		virtual uint32_t GetWidth() const  = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;

	};

	class Texture2D : public Texture
	{
	public:
		virtual ~Texture2D() = default;
		static Ref<Texture2D> Create(const std::string& path);
	};
}