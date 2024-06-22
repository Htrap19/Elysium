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
IncludeDir["STB"] = "%{wks.location}/engine/vendor/stb"
IncludeDir["ENTT"] = "%{wks.location}/engine/vendor/entt/src"
IncludeDir["ASSIMP"] = "%{wks.location}/engine/vendor/assimp/include"

IncludeDir["_CONFIG_HEADERS"] = "%{wks.location}/engine/vendor/_config_headers"

group "Dependencies"
	include "engine/vendor"
group ""

include "Engine"
include "Sandbox"
