project "Glad"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files {
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}
	
	includedirs {
		"include"
	}

	filter "system:windows"
		systemversion "latest"
		
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