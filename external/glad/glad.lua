INCLUDE_DIR["glad"] = "%{wks.location}/external/glad/include"

project "glad"
    kind "StaticLib"
    language "C"
    systemversion "latest"
    staticruntime "On"
    targetdir (TARGET_DIR)
    objdir (OBJECT_DIR)
    location (PROJECT_LOC)
    files
    {
        "src/**.h", "src/**.c"
    }
    includedirs
    {
        "include"
    }
    filter "platforms:x64"
        architecture "x64"
    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
    filter "configurations:Release"
        runtime "Release"
        optimize "On"