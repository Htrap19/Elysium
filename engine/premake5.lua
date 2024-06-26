project "Engine"
	kind "StaticLib"
	language "C++"
	staticruntime "On"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "%{prj.name}")
	objdir ("%{wks.location}/obj/" .. outputdir .. "%{prj.name}")

	includedirs
	{
		"src/",
		"vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.IMGUI}",
		"%{IncludeDir.STB}",
		"%{IncludeDir.ENTT}",
		"%{IncludeDir.ASSIMP}",
		"%{IncludeDir._CONFIG_HEADERS}",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
	}

	links
	{
		"GLFW",
		"ImGui",
		"Assimp",
		"opengl32.lib"
	}

	files
	{ 
		"src/**.cpp",
		"src/**.h",
		"vendor/glad/src/glad.c",
		"vendor/stb/stb_image.cpp",
	}

	filter "configurations:Debug"
		runtime "Debug"
		defines { "ES_DEBUG" }
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		defines { "ES_RELEASE" }
		optimize "On"

	filter "system:windows"
		defines { "ES_PLATFORM_WINDOWS" }