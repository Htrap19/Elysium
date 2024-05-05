workspace "Elysium"
	architecture ("x86_64")
	configurations { "Debug", "Release" }
	startproject "Sandbox"
	cppdialect "C++20"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Engine"
include "Sandbox"
