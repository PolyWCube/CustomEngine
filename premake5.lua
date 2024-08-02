workspace "CustomEngine"
	architecture "x64"
	configurations {
		"Debug",
		"Release"
	}
	startproject "Sandbox"

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "CustomEngine/vendor/GLFW"
include "CustomEngine/vendor/Glad"

project "CustomEngine"
	location "CustomEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "CustomPrecompileHeader.h"
	pchsource "CustomEngine/src/CustomPrecompileHeader.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs {
		"%{prj.name}/src",
		"CustomEngine/vendor/GLFW/include",
		"CustomEngine/vendor/Glad/include"
	}
	
	links {
		"CustomEngine/vendor/GLFW/lib/glfw3.lib",
		"Glad",
		"opengl32.lib"
	}
	
	filter "files:CustomEngine/src/Custom/Log/CustomLog.cpp" flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"

		defines {
			"CUSTOM_PLATFORM_WINDOWS",
			"CUSTOM_ENABLE_DEBUG",
			"_CRT_SECURE_NO_WARNINGS",
			"CUSTOM_ENABLE_ASSERTION"
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

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"CustomEngine/src"
	}

	links {
		"CustomEngine"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"CUSTOM_PLATFORM_WINDOWS",
			"_CRT_SECURE_NO_WARNINGS",
			"CUSTOM_ENABLE_ASSERTION"
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