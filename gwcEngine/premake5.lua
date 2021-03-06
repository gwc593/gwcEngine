workspace "gwcEngine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist",
		"Profiling"
	}

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "gwcEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "gwcEngine/vendor/Glad/include"
IncludeDir["glm"] = "gwcEngine/vendor/glm"
IncludeDir["stb_image"] = "gwcEngine/vendor/stb_image"
IncludeDir["tinyxml"] = "gwcEngine/vendor/tinyxml"

include "gwcEngine/vendor/GLFW"
include "gwcEngine/vendor/Glad"
include "gwcEngine/vendor/tinyxml"

project "gwcEngine"
	characterset ("MBCS")
	location"gwcEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputDir .. "/%{prj.name}")
	objdir("bin-int/" .. outputDir .. "/%{prj.name}")

	pchheader "gepch.h"
	pchsource "gwcEngine/src/gepch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.hpp",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/tinyxml",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}
	
	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib",
		"tinyxml"
	}

	filter "system:windows"
		systemversion "latest"

	defines
	{
		"GLEW_STATIC",
		"GE_PLATFORM_WINDOWS",
		"GE_BUILD_DLL",
		"GLFW_INCLUDE_NONE",
		"TIXML_USE_STL"
	}


	filter "configurations:Debug"
		defines {"GE_DEBUG","GE_ENABLE_ASSERTS"}
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines{"GE_PROFILING","GE_DIST"}
		runtime "Release"
		optimize "on"
		
	filter "configurations:Profiling"
		runtime "Release"
		defines{"GE_PROFILING","GE_DIST"}
		optimize "on"



project "sandbox"
	location"sandbox"
	kind "ConsoleApp"
	
	cppdialect "C++17"
	language "C++"
	staticruntime "On"


	targetdir("bin/" .. outputDir .. "/%{prj.name}")
	objdir("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"gwcEngine/vendor/spdlog/include",
		"gwcEngine/vendor/tinyxml",
		"gwcEngine/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"gwcEngine"
	}

	filter "system:windows"
		systemversion "latest"

	defines
	{
		"GLEW_STATIC",
		"GE_PLATFORM_WINDOWS",
		"TIXML_USE_STL"
	}


	filter "configurations:Debug"
		defines "GE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GE_DIST"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Profiling"
		runtime "Release"
		defines{"GE_PROFILING","GE_DIST"}
		optimize "on"