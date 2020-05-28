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
include "/gwcEngine/vendor/GLFW"

project "gwcEngine"

	location"gwcEngine"
	kind "SharedLib"
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
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}
	
	links
	{
		"GLFW",
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
		symbols "On"

	filter "configurations:Release"
		defines "GE_RELEASE"
		optimize "On"

	filter "configurations:Debug"
		defines "GE_DIST"
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
		symbols "On"

	filter "configurations:Release"
		defines "GE_RELEASE"
		optimize "On"

	filter "configurations:Debug"
		defines "GE_DIST"
		optimize "On"


