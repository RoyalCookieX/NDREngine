APP_INCLUDE_DIR["glfw"] = "external/glfw/include"
ENGINE_INCLUDE_DIR["glfw"] = "%{wks.location}/%{APP_INCLUDE_DIR.glfw}"

project "glfw"
    kind "StaticLib"
    language "C"
    targetdir (TARGET_DIR)
    objdir (OBJECT_DIR)
    files
    {
        "include/GLFW/*.h",

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
    filter "platforms:x64"
        architecture "x64"
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
    filter "configurations:debug"
        runtime "Debug"
        symbols "On"
    filter "configurations:release"
        runtime "Release"
        optimize "On"