workspace "gwcEngine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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

	include
	{
		"%{prj.name}/vendor/spdlog/include"
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

	postbuild
	{
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/sandbox")
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
	

