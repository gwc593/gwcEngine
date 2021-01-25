project "tinyxml"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"**.h",
		"**.hpp",
		"**.cpp"
	}

	defines 
	{ 
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
		defines "GE_DIST"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Profiling"
		runtime "Release"
		defines{"GE_PROFILING","GE_DIST"}
		optimize "on"