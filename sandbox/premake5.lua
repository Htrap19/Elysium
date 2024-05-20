project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "on"
	links { "Engine" }

	targetdir ("%{wks.location}/bin/" .. outputdir .. "%{prj.name}")
	objdir ("%{wks.location}/obj/" .. outputdir .. "%{prj.name}")

	includedirs 
	{
		"%{wks.location}/engine/vendor/spdlog/include",
		"../Engine/src",
		"%{IncludeDir.IMGUI}",
		"%{IncludeDir.GLM}"
	}

	files { "**.cpp", "**.h" }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"