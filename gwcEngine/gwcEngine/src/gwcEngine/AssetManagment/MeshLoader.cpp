#include"gepch.h"
#include "MeshLoader.h"

namespace gwcEngine
{

	void doSomething()
	{
		int a;
	}

	Mesh MeshLoader::LoadMesh(const std::string& path, MeshFormat format)
	{
		if (format == MeshFormat::DAE) {

			std::string meshData = FileSystem::GetInstance()->ReadToString(path);

			TiXmlDocument doc(path);
			doc.LoadFile();
		}
		Mesh a;
		return a;
	}
}