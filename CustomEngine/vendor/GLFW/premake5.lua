project "GLFW"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	filter "system:windows"
		systemversion "latest"

		defines {
			"GLFW_WIN32",
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