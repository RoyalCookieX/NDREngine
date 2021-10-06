APP_INCLUDE_DIR["tiny_obj_loader"] = "external/tiny_obj_loader/include"
ENGINE_INCLUDE_DIR["tiny_obj_loader"] = "%{wks.location}/%{APP_INCLUDE_DIR.tiny_obj_loader}"

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