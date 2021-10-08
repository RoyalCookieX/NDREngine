APP_INCLUDE_DIR["stb_image"] = "external/stb_image/include"
ENGINE_INCLUDE_DIR["stb_image"] = "%{wks.location}/%{APP_INCLUDE_DIR.stb_image}"

project "stb_image"
    kind "StaticLib"
    language "C"
    targetdir (TARGET_DIR)
    objdir (OBJECT_DIR)
    files
    {
        "include/*.h",
		"src/*.c",
    }
    includedirs
    {
        "include"
    }
    filter "platforms:x64"
        architecture "x64"
    filter "system:windows"
        systemversion "latest"
        staticruntime "On"
    filter "configurations:debug"
        runtime "Debug"
        symbols "On"
    filter "configurations:release"
        runtime "Release"
        optimize "On"