project "engine"
    targetname "NDREngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    systemversion "latest"
    staticruntime "On"
    targetdir (TARGET_DIR)
    objdir (OBJECT_DIR)
    pchheader "ndrpch.h"
    pchsource "source/ndrpch.cpp"
    defines "NDR_GRAPHICSAPI_OPENGL"
    files
    {
        "source/**.h", "source/**.cpp"
    }
    removefiles
    {
        "source/ndrpch.cpp",
        "source/platform/**.h", "source/platform/**.cpp",
    }
    includedirs
    {
        "source",
        "%{ENGINE_INCLUDE_DIR.glfw}",
        "%{ENGINE_INCLUDE_DIR.glad}",
        "%{ENGINE_INCLUDE_DIR.glm}",
        "%{ENGINE_INCLUDE_DIR.stb_image}",
        "%{ENGINE_INCLUDE_DIR.tiny_obj_loader}",
    }
    links
    {
        "glad",
        "glfw",
        "stb_image",
        "tiny_obj_loader",
        "opengl32"
    }
    filter "system:windows"
        defines "NDR_PLATFORM_WINDOWS"
        files 
        { 
            "source/ndrpch.cpp",
            "source/api/platform/*_win32.h", "source/api/platform/*_win32.cpp",
        }
    filter "platforms:x64"
        architecture "x64"
    filter "configurations:debug"
        defines "NDR_DEBUG"
        runtime "Debug"
        symbols "On"
        targetsuffix "_d"
    filter "configurations:release"
        defines "NDR_RELEASE"
        runtime "Release"
        optimize "On"