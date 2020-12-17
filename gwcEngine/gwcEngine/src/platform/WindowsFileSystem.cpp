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
			int bytes = GetModuleFileName(NULL, runtimeDir, len);

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
}