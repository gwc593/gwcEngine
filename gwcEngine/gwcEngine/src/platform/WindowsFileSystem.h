#pragma once
#include "gwcEngine/Core/FileSystem.h"
namespace gwcEngine 
{
	class WindowsFileSystem : public FileSystem
	{
	public:

		WindowsFileSystem()
		{
			GetRuntimePath();
		}

		virtual bool MakeDir(const std::string& relPath) override;
		virtual bool DelDir(const std::string& relPath) override;

		virtual bool MakeFile(const std::string& relPath) override { return false; };
		virtual bool DelFile(const std::string& relPath) override { return false; };

		virtual const std::string& GetRuntimePath() override;

		std::string ReadToString(const std::string& relPath) override;

		virtual const std::string& GetWorkingDirectory()
		{
			return m_WorkingDirectory;
		}

	};
}