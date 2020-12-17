#include"gepch.h"
#include"FileSystem.h"
#include"Platform/WindowsFileSystem.h"
#include<string>
namespace gwcEngine 
{
	FileSystem* FileSystem::s_Instance = nullptr;

	PlatformOS FileSystem::m_Platform = PlatformOS::None;

	const PlatformOS& FileSystem::GetPlatform()
	{
		#ifdef GE_PLATFORM_WINDOWS
				m_Platform = PlatformOS::Windows;
		#endif // GE_PLATFORM_WINDOWS

		return m_Platform;

	}

	FileSystem* FileSystem::GetInstance()
	{
		if (s_Instance != nullptr)
			return s_Instance;

		


		switch (GetPlatform()) {
			case PlatformOS::None:
				GE_CORE_ASSERT(false, "No OS selected...");
				return nullptr;

			case PlatformOS::Windows: return new WindowsFileSystem;
		}

		GE_CORE_ASSERT(false, "Invalid Rendering API selected");
	}
}