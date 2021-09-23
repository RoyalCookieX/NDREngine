project "engine"
    targetname "NDREngine"
    language "C++"
    cppdialect "C++17"
    systemversion "latest"
    staticruntime "On"
    targetdir (TARGET_DIR)
    objdir (OBJECT_DIR)
    files
    {
        "source/**.h", "source/**.cpp"
    }
    includedirs
    {
        "source",
        "%{INCLUDE_DIR.glad}",
        "%{INCLUDE_DIR.glfw}",
        "%{INCLUDE_DIR.glm}",
        "%{INCLUDE_DIR.stb_image}",
        "%{INCLUDE_DIR.tiny_obj_loader}",
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
    filter "platforms:x64"
        architecture "x64"
    filter "configurations:Debug"
        kind "ConsoleApp"
        defines "NDR_DEBUG"
        runtime "Debug"
        symbols "On"
        targetsuffix "_d"
    filter "configurations:Release"
        kind "WindowedApp"
        defines "NDR_RELEASE"
        runtime "Release"
        optimize "On"