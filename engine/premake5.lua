project "Engine"
	kind "StaticLib"
	language "C++"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "%{prj.name}")
	objdir ("%{wks.location}/obj/" .. outputdir .. "%{prj.name}")

	includedirs
	{
		"vendor/spdlog/include"
	}

	files { "**.cpp", "**.h" }

	filter "configurations:Debug"
		defines { "ES_DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "ES_RELEASE" }
		optimize "On"