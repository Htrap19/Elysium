project "GLFW"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "%{prj.name}")
	objdir ("%{wks.location}/obj/" .. outputdir .. "%{prj.name}")

	files
	{
		"glfw/include/GLFW/glfw3.h",
		"glfw/include/GLFW/glfw3native.h",
		"glfw/src/internal.h",
		"glfw/src/platform.h",
		"glfw/src/mappings.h",
        "glfw/src/context.c",
		"glfw/src/init.c", 
		"glfw/src/input.c", 
		"glfw/src/monitor.c", 
		"glfw/src/platform.c",
		"glfw/src/vulkan.c",
		"glfw/src/window.c",
		"glfw/src/egl_context.c",
		"glfw/src/osmesa_context.c",
		"glfw/src/null_platform.h", 
		"glfw/src/null_joystick.h",
		"glfw/src/null_init.c", 
		"glfw/src/null_monitor.c", 
		"glfw/src/null_window.c",
		"glfw/src/null_joystick.c"
	}

	filter "system:windows"
		systemversion "latest"

		files
		{
			"glfw/src/win32_time.h",
			"glfw/src/win32_thread.h",
			"glfw/src/win32_module.c",
			"glfw/src/win32_time.c",
			"glfw/src/win32_thread.c",
			"glfw/src/win32_platform.h",
			"glfw/src/win32_joystick.h",
			"glfw/src/win32_init.c",
			"glfw/src/win32_joystick.c",
			"glfw/src/win32_monitor.c",
			"glfw/src/win32_window.c",
			"glfw/src/wgl_context.c"
		}

		defines
		{
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

project "ImGui"
    kind "StaticLib"
    language "C++"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "%{prj.name}")
	objdir ("%{wks.location}/obj/" .. outputdir .. "%{prj.name}")

    files
    {
        "imgui/imconfig.h",
        "imgui/imgui.h",
        "imgui/imgui.cpp",
        "imgui/imgui_draw.cpp",
        "imgui/imgui_internal.h",
        "imgui/imgui_widgets.cpp",
        "imgui/imstb_rectpack.h",
        "imgui/imstb_textedit.h",
        "imgui/imstb_truetype.h",
        "imgui/imgui_tables.cpp",
        "imgui/imgui_demo.cpp"
    }

    filter "system:windows"
        systemversion "latest"
        cppdialect "C++20"
        staticruntime "On"

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"