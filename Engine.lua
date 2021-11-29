include "Defines"

project "Engine"
    targetname "NDREngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    systemversion "latest"
    staticruntime "On"
    targetdir (TARGET_DIR)
    objdir (OBJECT_DIR)
    pchheader "Ndrpch.h"
    pchsource "Source/ndrpch.cpp"
    defines "NDR_GRAPHICSAPI_OPENGL"
    files
    {
        "Source/**.h", "Source/**.cpp",
        "Assets/**";
    }
    removefiles
    {
        "Source/ndrpch.cpp",
        "Source/platform/**.h", "Source/platform/**.cpp",
    }
    includedirs
    {
        "Source",
        "External/glad/include",
        "External/glfw/include",
        "External/glm/include",
        "External/json/single_include",
        "External/stb_image/include",
        "External/tiny_obj_loader/include",
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
            "Source/ndrpch.cpp",
            "Source/API/Platform/*_win32.h", "Source/API/Platform/*_win32.cpp",
        }
    filter "platforms:x64"
        architecture "x64"
    filter "system:windows"
        defines "NDR_PLATFORM_WINDOWS"
    filter "configurations:Debug"
        defines "NDR_DEBUG"
        runtime "Debug"
        symbols "On"
    filter "configurations:Release"
        defines "NDR_RELEASE"
        runtime "Release"
        optimize "On"