workspace "gwcEngine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "gwcEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "gwcEngine/vendor/Glad/include"

include "gwcEngine/vendor/GLFW"
include "gwcEngine/vendor/Glad"

project "gwcEngine"

	location"gwcEngine"
	kind "SharedLib"
	language "C++"

	targetdir("bin/" .. outputDir .. "/%{prj.name}")
	objdir("bin-int/" .. outputDir .. "/%{prj.name}")

	pchheader "gepch.h"
	pchsource "gwcEngine/src/gepch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
	}
	
	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	defines
	{
		"GLEW_STATIC",
		"GE_PLATFORM_WINDOWS",
		"GE_BUILD_DLL"
	}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/sandbox")
	}


	filter "configurations:Debug"
		defines {"GE_DEBUG","GE_ENABLE_ASSERTS"}
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "GE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Debug"
		defines "GE_DIST"
		buildoptions "/MD"
		optimize "On"


project "sandbox"
	location"sandbox"
	kind "ConsoleApp"

	language "C++"


	targetdir("bin/" .. outputDir .. "/%{prj.name}")
	objdir("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"gwcEngine/vendor/spdlog/include",
		"gwcEngine/src",
	}

	links
	{
		"gwcEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	defines
	{
		"GLEW_STATIC",
		"GE_PLATFORM_WINDOWS",
	}


	filter "configurations:Debug"
		defines "GE_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "GE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Debug"
		defines "GE_DIST"
		buildoptions "/MD"
		optimize "On"


