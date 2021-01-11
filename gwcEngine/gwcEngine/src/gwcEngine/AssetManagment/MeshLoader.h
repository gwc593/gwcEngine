#pragma once
#include "gwcEngine/Components/Render/Mesh.h"
namespace gwcEngine
{
	enum class MeshFormat
	{
		None = 0,
		OJB,
		DAE
	};

	class MeshLoader
	{
		static Mesh LoadMesh(const std::string& path, MeshFormat format=MeshFormat::None);
	};
}