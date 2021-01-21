#pragma once
#include"tinyxml.h"
#include "gwcEngine/Components/Renderable/Mesh.h"
namespace gwcEngine
{
	enum class ModelFormat
	{
		None = 0,
		OJB,
		DAE
	};

	class ModelLoader
	{
	public:
		static Ref<Entity> LoadModel(const std::string& path, ModelFormat format= ModelFormat::None);
	};
}