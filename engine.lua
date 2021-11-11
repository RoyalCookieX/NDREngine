project "Engine"
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
        "source/**.h", "source/**.cpp",
        "assets/**";
    }
    removefiles
    {
        "source/ndrpch.cpp",
        "source/platform/**.h", "source/platform/**.cpp",
    }
    includedirs
    {
        "source",
        "external/glad/include",
        "external/glfw/include",
        "external/glm/include",
        "external/stb_image/include",
        "external/tiny_obj_loader/include",
        "external/mini/include",
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