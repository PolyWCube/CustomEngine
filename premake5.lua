workspace "CustomEngine"
	architecture "x64"
	configurations
	{
		"Debug",
		"Release"
	}
	startproject "Sandbox"

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "CustomEngine"
	location "CustomEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "CustomPrecompiledHeader.h"
	pchsource "CustomEngine/src/CustomPrecompiledHeader.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CUSTOM_PLATFORM_WINDOWS",
			"CUSTOM_ENABLE_DEBUG",
			"GLFW_INCLUDE_NONE",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		defines "CUSTOM_DEBUG"
		runtime "Debug"
		buildoptions "/MDd"
		symbols "on"
		linkoptions { "/NODEFAULTLIB:LIBCMT" }

	filter "configurations:Release"
		defines "CUSTOM_RELEASE"
		runtime "Release"
		buildoptions "/MD"
		symbols "on"
		optimize "on"
		linkoptions { "/NODEFAULTLIB:LIBCMT" }

project "CustomApplication"
	location "CustomApplication"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"CustomEngine/src",
		"CustomEngine/vendor"
	}

	links 
	{
		"CustomEngine"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CUSTOM_PLATFORM_WINDOWS",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		defines "CUSTOM_DEBUG"
		runtime "Debug"
		buildoptions "/MDd"
		symbols "on"
		linkoptions { "/NODEFAULTLIB:LIBCMT" }

	filter "configurations:Release"
		defines "CUSTOM_RELEASE"
		runtime "Release"
		buildoptions "/MD"
		symbols "on"
		optimize "on"
		linkoptions { "/NODEFAULTLIB:LIBCMT" }