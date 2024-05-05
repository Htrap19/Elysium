project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	links { "Engine" }

	targetdir ("%{wks.location}/bin/" .. outputdir .. "%{prj.name}")
	objdir ("%{wks.location}/obj/" .. outputdir .. "%{prj.name}")

	includedirs 
	{
		"%{wks.location}/engine/vendor/spdlog/include",
		"../Engine/src"
	}

	files { "**.cpp", "**.h" }

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		optimize "On"