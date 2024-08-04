cmake_minimum_required(VERSION 3.5)

project(Elysium LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SPDLOG_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/engine/vendor/spdlog/include" CACHE INTERNAL "")
set(GLFW_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/engine/vendor/glfw/include" CACHE INTERNAL "")
set(GLAD_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/engine/vendor/glad/include" CACHE INTERNAL "")
set(IMGUI_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/engine/vendor/imgui" CACHE INTERNAL "")
set(GLM_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/engine/vendor/glm" CACHE INTERNAL "")
set(STB_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/engine/vendor/stb" CACHE INTERNAL "")
set(ENTT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/engine/vendor/entt/src" CACHE INTERNAL "")
set(ASSIMP_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/engine/vendor/assimp/include" CACHE INTERNAL "")

set(_CONFIG_HEADERS_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/engine/vendor/_config_headers" CACHE INTERNAL "")

if (WIN32)
    add_compile_definitions(ES_PLATFORM_WINDOWS)
elseif(UNIX)
    add_compile_definitions(ES_PLATFORM_UNIX)
endif()

add_subdirectory(engine)
add_subdirectory(sandbox)

install(TARGETS Sandbox
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
