#pragma once
#include<string>
namespace gwcEngine 
{
	enum class PlatformOS
	{
		None = 0,
		Windows,
		OSX,
		Linux
	};

	class FileSystem
	{
	public:
		FileSystem() = default;
		~FileSystem() = default;

		static FileSystem* GetInstance();

		virtual bool MakeDir(const std::string& relPath) = 0;
		virtual bool DelDir(const std::string& relPath) = 0;

		virtual bool MakeFile(const std::string& relPath) = 0;
		virtual bool DelFile(const std::string& relPath) = 0;

		virtual const std::string& GetRuntimePath() = 0;
		virtual const std::string& GetWorkingDirectory() = 0;
		
		virtual std::string ReadToString(const std::string& relPath) = 0;

		void SetWorkingDirectory(const std::string& address)
		{
			m_WorkingDirectory = address;
		}

		static const PlatformOS& GetPlatform();
	protected:
		std::string m_RunTimePath;
		std::string m_WorkingDirectory;
	private:

		static PlatformOS m_Platform;
		static FileSystem* s_Instance;
		
	};

}