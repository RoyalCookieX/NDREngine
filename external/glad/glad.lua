APP_INCLUDE_DIR["glad"] = "external/glad/include"
ENGINE_INCLUDE_DIR["glad"] = "%{wks.location}/%{APP_INCLUDE_DIR.glad}"

project "glad"
    kind "StaticLib"
    language "C"
    systemversion "latest"
    staticruntime "On"
    targetdir (TARGET_DIR)
    objdir (OBJECT_DIR)
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
    filter "platforms:x86"
        architecture "x86"
    filter "configurations:debug"
        runtime "Debug"
        symbols "On"
    filter "configurations:release"
        runtime "Release"
        optimize "On"