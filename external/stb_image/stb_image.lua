INCLUDE_DIR["stb_image"] = "%{wks.location}/external/stb_image/include"

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
    filter "system:windows"
        systemversion "latest"
        staticruntime "On"
    filter "platforms:x64"
        architecture "x64"
    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
    filter "configurations:Release"
        runtime "Release"
        optimize "On"