INCLUDE_DIR["tiny_obj_loader"] = "%{wks.location}/external/tiny_obj_loader/include"

project "tiny_obj_loader"
    kind "StaticLib"
    language "C++"
    targetdir (TARGET_DIR)
    objdir (OBJECT_DIR)
    files
    {
        "include/*.h",
		"src/*.cpp",
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