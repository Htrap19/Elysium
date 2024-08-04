find_package(OpenGL REQUIRED)

add_subdirectory(vendor)

file(GLOB_RECURSE ENGINE_SOURCES
    src/core/*.cpp
    src/core/*.h
    src/event/*.cpp
    src/event/*.h
    src/imgui/*.cpp
    src/imgui/*.h
    src/renderer/*.cpp
    src/renderer/*.h
    src/scene/*.cpp
    src/scene/*.h
    src/platform/opengl/*.cpp
    src/platform/opengl/*.h
)

if (WIN32)
    set (ENGINE_SOURCES ${ENGINE_SOURCES}
        src/platform/windows/windowsinput.cpp
        src/platform/windows/windowswindow.h
        src/platform/windows/windowswindow.cpp
    )
elseif (UNIX)
    set (ENGINE_SOURCES ${ENGINE_SOURCES}
        src/platform/x11/x11input.cpp
        src/platform/x11/x11window.h
        src/platform/x11/x11window.cpp
    )
endif()

add_library(Engine STATIC
    ${ENGINE_SOURCES}
    src/engine.h
    "vendor/glad/src/glad.c"
    "vendor/stb/stb_image.cpp")

target_compile_definitions(Engine PUBLIC
    _CRT_SECURE_NO_WARNINGS
    GLFW_INCLUDE_NONE)

target_include_directories(Engine PUBLIC
    "src/"
    ${SPDLOG_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    ${GLAD_INCLUDE_DIR}
    ${STB_INCLUDE_DIR}
    ${IMGUI_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    ${ENTT_INCLUDE_DIR}
    ${ASSIMP_INCLUDE_DIR}
    ${_CONFIG_HEADERS_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIRS})

target_link_libraries(Engine PUBLIC
    OpenGL::GL
    GLFW ImGui Assimp)
