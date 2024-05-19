workspace "Elysium"
	architecture ("x86_64")
	configurations { "Debug", "Release" }
	startproject "Sandbox"
	cppdialect "C++20"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/engine/vendor/glfw/include"
IncludeDir["GLAD"] = "%{wks.location}/engine/vendor/glad/include"

group "Dependencies"
	include "engine/vendor/glfw"
group ""

include "Engine"
include "Sandbox"
