INCLUDE_DIR["glfw"] = "%{wks.location}/external/glfw/include"

project "glfw"
    kind "StaticLib"
    language "C"
    targetdir (TARGET_DIR)
    objdir (OBJECT_DIR)
    location (PROJECT_LOC)
    files
    {
        "include/GLFW/*.h",

		"src/glfw_config.h",
		"src/context.c",
		"src/init.c",
		"src/input.c",
		"src/monitor.c",
		"src/vulkan.c",
		"src/window.c"
    }
    includedirs
    {
        "include"
    }
    filter "system:windows"
        systemversion "latest"
        staticruntime "On"
        files
        {
            "src/win32_*.c",
			"src/wgl_context.c",
			"src/egl_context.c",
			"src/osmesa_context.c"
        }
        defines
        {
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }
    filter "platforms:x64"
        architecture "x64"
    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
    filter "configurations:Release"
        runtime "Release"
        optimize "On"