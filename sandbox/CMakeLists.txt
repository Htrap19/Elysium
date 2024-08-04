file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)

add_executable(Sandbox ${SOURCES})

target_include_directories(Sandbox PUBLIC
    ${SPDLOG_INCLUDE_DIR}
    "${PROJECT_SOURCE_DIR}/engine/src"
    ${IMGUI_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    ${ENTT_INCLUDE_DIR})

target_link_libraries(Sandbox Engine)
