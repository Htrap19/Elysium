workspace "Elysium"
	architecture ("x86_64")
	configurations { "Debug", "Release" }
	startproject "Sandbox"
	cppdialect "C++20"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/engine/vendor/glfw/include"
IncludeDir["GLAD"] = "%{wks.location}/engine/vendor/glad/include"
IncludeDir["GLM"] = "%{wks.location}/engine/vendor/glm"
IncludeDir["IMGUI"] = "%{wks.location}/engine/vendor/imgui"


group "Dependencies"
	include "engine/vendor"
group ""

include "Engine"
include "Sandbox"
