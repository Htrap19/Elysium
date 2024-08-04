# GLFW =====================================
set (GLFW_SOURCES
    glfw/include/GLFW/glfw3.h
    glfw/include/GLFW/glfw3native.h
    glfw/src/internal.h
    glfw/src/platform.h
    glfw/src/mappings.h
    glfw/src/context.c
    glfw/src/init.c
    glfw/src/input.c
    glfw/src/monitor.c
    glfw/src/platform.c
    glfw/src/vulkan.c
    glfw/src/window.c
    glfw/src/egl_context.c
    glfw/src/osmesa_context.c
    glfw/src/null_platform.h
    glfw/src/null_joystick.h
    glfw/src/null_init.c
    glfw/src/null_monitor.c
    glfw/src/null_window.c
    glfw/src/null_joystick.c
)

if (WIN32)
    set (GLFW_SOURCES ${GLFW_SOURCES}
        glfw/src/win32_time.h
        glfw/src/win32_thread.h
        glfw/src/win32_module.c
        glfw/src/win32_time.c
        glfw/src/win32_thread.c
        glfw/src/win32_platform.h
        glfw/src/win32_joystick.h
        glfw/src/win32_init.c
        glfw/src/win32_joystick.c
        glfw/src/win32_monitor.c
        glfw/src/win32_window.c
        glfw/src/wgl_context.c
    )
elseif (UNIX)
    set (GLFW_SOURCES ${GLFW_SOURCES}
        glfw/src/posix_time.h
        glfw/src/posix_thread.h
        glfw/src/posix_module.c
        glfw/src/posix_time.c
        glfw/src/posix_thread.c
        glfw/src/x11_platform.h
        glfw/src/xkb_unicode.h
        glfw/src/x11_init.c
        glfw/src/x11_monitor.c
        glfw/src/x11_window.c
        glfw/src/xkb_unicode.c
        glfw/src/glx_context.c
        glfw/src/linux_joystick.h
        glfw/src/linux_joystick.c
        glfw/src/posix_poll.h
        glfw/src/posix_poll.c
    )
endif()

add_library(GLFW STATIC ${GLFW_SOURCES})

if (WIN32)
    target_compile_definitions(GLFW PRIVATE
        _GLFW_WIN32
        _CRT_SECURE_NO_WARNINGS)
elseif (UNIX)
    target_compile_definitions(GLFW PRIVATE
        _GLFW_X11)
endif()
# ==========================================

# IMGUI ====================================
set (IMGUI_SOURCES
    imgui/imconfig.h
    imgui/imgui.h
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_internal.h
    imgui/imgui_widgets.cpp
    imgui/imstb_rectpack.h
    imgui/imstb_textedit.h
    imgui/imstb_truetype.h
    imgui/imgui_tables.cpp
    imgui/imgui_demo.cpp
    imgui/misc/cpp/imgui_stdlib.h
    imgui/misc/cpp/imgui_stdlib.cpp
)

add_library(ImGui STATIC ${IMGUI_SOURCES})

target_include_directories(ImGui PRIVATE "imgui")
# ==========================================

# ASSIMP ===================================
file(GLOB ASSIMP_CONTRIB_SOURCE_FILES
    assimp/contrib/Open3DGC/*
    assimp/contrib/unzip/*
    assimp/contrib/zlib/*.c)
file(GLOB_RECURSE ASSIMP_SOURCE_FILES
    assimp/include/*.cpp
    assimp/code/*.cpp)
set(ASSIMP_SOURCE_FILES
    ${ASSIMP_SOURCE_FILES}
    ${ASSIMP_CONTRIB_SOURCE_FILES})
add_compile_definitions(ASSIMP_BUILD_NO_OWN_ZLIB)

add_compile_definitions(ASSIMP_BUILD_NO_X_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_3DS_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_3DS_EXPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_MD3_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_MDL_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_MD2_IMPORTER)
# add_compile_definitions(ASSIMP_BUILD_NO_PLY_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_ASE_IMPORTER)
# add_compile_definitions(ASSIMP_BUILD_NO_OBJ_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_AMF_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_HMP_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_SMD_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_MDC_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_MD5_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_STL_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_LWO_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_DXF_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_NFF_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_RAW_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_OFF_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_AC_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_BVH_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_IRRMESH_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_IRR_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_Q3D_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_B3D_IMPORTER)
# add_compile_definitions(ASSIMP_BUILD_NO_COLLADA_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_TERRAGEN_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_CSM_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_3D_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_LWS_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_OGRE_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_OPENGEX_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_MS3D_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_COB_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_BLEND_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_Q3BSP_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_NDO_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_IFC_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_XGL_IMPORTER)
# add_compile_definitions(ASSIMP_BUILD_NO_FBX_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_ASSBIN_IMPORTER)
# add_compile_definitions(ASSIMP_BUILD_NO_GLTF_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_C4D_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_3MF_IMPORTER)
# add_compile_definitions(ASSIMP_BUILD_NO_X3D_IMPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_MMD_IMPORTER)

add_compile_definitions(ASSIMP_BUILD_NO_STEP_EXPORTER)
add_compile_definitions(ASSIMP_BUILD_NO_SIB_IMPORTER)

# add_compile_definitions(ASSIMP_BUILD_NO_MAKELEFTHANDED_PROCESS)
# add_compile_definitions(ASSIMP_BUILD_NO_FLIPUVS_PROCESS)
# add_compile_definitions(ASSIMP_BUILD_NO_FLIPWINDINGORDER_PROCESS)
# add_compile_definitions(ASSIMP_BUILD_NO_CALCTANGENTS_PROCESS)
add_compile_definitions(ASSIMP_BUILD_NO_JOINVERTICES_PROCESS)
# add_compile_definitions(ASSIMP_BUILD_NO_TRIANGULATE_PROCESS)
add_compile_definitions(ASSIMP_BUILD_NO_GENFACENORMALS_PROCESS)
# add_compile_definitions(ASSIMP_BUILD_NO_GENVERTEXNORMALS_PROCESS)
add_compile_definitions(ASSIMP_BUILD_NO_REMOVEVC_PROCESS)
add_compile_definitions(ASSIMP_BUILD_NO_SPLITLARGEMESHES_PROCESS)
add_compile_definitions(ASSIMP_BUILD_NO_PRETRANSFORMVERTICES_PROCESS)
add_compile_definitions(ASSIMP_BUILD_NO_LIMITBONEWEIGHTS_PROCESS)
# add_compile_definitions(ASSIMP_BUILD_NO_VALIDATEDS_PROCESS)
add_compile_definitions(ASSIMP_BUILD_NO_IMPROVECACHELOCALITY_PROCESS)
add_compile_definitions(ASSIMP_BUILD_NO_FIXINFACINGNORMALS_PROCESS)
add_compile_definitions(ASSIMP_BUILD_NO_REMOVE_REDUNDANTMATERIALS_PROCESS)
add_compile_definitions(ASSIMP_BUILD_NO_FINDINVALIDDATA_PROCESS)
add_compile_definitions(ASSIMP_BUILD_NO_FINDDEGENERATES_PROCESS)
add_compile_definitions(ASSIMP_BUILD_NO_SORTBYPTYPE_PROCESS)
add_compile_definitions(ASSIMP_BUILD_NO_GENUVCOORDS_PROCESS)
add_compile_definitions(ASSIMP_BUILD_NO_TRANSFORMTEXCOORDS_PROCESS)
add_compile_definitions(ASSIMP_BUILD_NO_FINDINSTANCES_PROCESS)
add_compile_definitions(ASSIMP_BUILD_NO_OPTIMIZEMESHES_PROCESS)
add_compile_definitions(ASSIMP_BUILD_NO_OPTIMIZEGRAPH_PROCESS)
add_compile_definitions(ASSIMP_BUILD_NO_SPLITBYBONECOUNT_PROCESS)
add_compile_definitions(ASSIMP_BUILD_NO_DEBONE_PROCESS)
add_compile_definitions(ASSIMP_BUILD_NO_EMBEDTEXTURES_PROCESS)
add_compile_definitions(ASSIMP_BUILD_NO_GLOBALSCALE_PROCESS)

add_compile_definitions(MINIZ_USE_UNALIGNED_LOADS_AND_STORES=0)
add_compile_definitions(ASSIMP_IMPORTER_GLTF_USE_OPEN3DGC=1)
add_compile_definitions(RAPIDJSON_HAS_STDSTRING=1)
add_compile_definitions(RAPIDJSON_NOMEMBERITERATORCLASS)
add_compile_definitions(OPENDDLPARSER_BUILD)

add_library(Assimp STATIC ${ASSIMP_SOURCE_FILES})
target_include_directories(Assimp PUBLIC
        _config_headers/
        assimp
        assimp/include
        assimp/contrib
        assimp/code
        assimp/contrib/pugixml/src
        assimp/contrib/rapidjson/include
        assimp/contrib/unzip
        assimp/contrib/zlib
        assimp/contrib/utf8cpp/source)
# ==========================================
