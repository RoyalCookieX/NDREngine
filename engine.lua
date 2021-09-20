project "Engine"
    kind "WindowedApp"
    targetname "NDREngine"
    language "C++"
    cppdialect "C++17"
    systemversion "latest"
    staticruntime "On"
    targetdir (TARGET_DIR)
    objdir (OBJECT_DIR)
    location (PROJECT_LOC)
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
    }
    links
    {
        "glad",
        "glfw",
        "opengl32"
    }
    filter "system:windows"
        defines "NDR_PLATFORM_WINDOWS"
    filter "platforms:x64"
        architecture "x64"
    filter "configurations:Debug"
        defines "NDR_DEBUG"
        runtime "Debug"
        symbols "On"
        targetsuffix "_d"
    filter "configurations:Release"
        defines "NDR_RELEASE"
        runtime "Release"
        optimize "On"