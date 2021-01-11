#include "gepch.h"
#include "WindowsFileSystem.h"

namespace gwcEngine 
{
	const std::string& WindowsFileSystem::GetRuntimePath()
	{
		if (m_RunTimePath == "") {

			//discover current runtime path
			char runtimeDir[MAX_PATH];
			memset(runtimeDir, '\0', MAX_PATH);

			size_t len = sizeof(runtimeDir);
			int bytes = GetModuleFileName(NULL, runtimeDir, (DWORD)len);

			if (!bytes) {
				GE_CORE_ASSERT(false, "Unable to get working directory");
			}

			int j = MAX_PATH - 1;

			while (runtimeDir[j] != '\\' && j > 0) {
				runtimeDir[j--] = '\0';
			}

			m_RunTimePath = std::string(runtimeDir);
			m_WorkingDirectory = m_RunTimePath;
			MakeDir("TempProjectArea");
			m_WorkingDirectory = m_RunTimePath + std::string("TempProjectArea\\");
		}

		return m_RunTimePath;
	}

	bool WindowsFileSystem::MakeDir(const std::string& address)
	{
		if (CreateDirectory((m_WorkingDirectory+address).c_str(), NULL) ||
			ERROR_ALREADY_EXISTS == GetLastError()) {
			return true;
		}
	
		GE_CORE_ERROR("unable to create directory at: {0}", m_WorkingDirectory + address);
		return false;
	}

	bool WindowsFileSystem::DelDir(const std::string& address)
	{
		if (RemoveDirectory((m_WorkingDirectory + address).c_str())) {
			return true;
		}

		GE_CORE_ERROR("unable to remove directory at: {0}", m_WorkingDirectory + address);
		return false;
	}

	std::string WindowsFileSystem::ReadToString(const std::string& relPath)
	{
		std::string result;

		std::ifstream in(relPath, std::ios::in, std::ios::binary);

		if (in) {
			//get size of shader def file
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());

			//go back to start of file
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else {
			GE_CORE_ERROR("could not open file '{0}'", relPath);
		}

		return result;
	}
}