TARGET_DIR = "%{wks.location}/binaries/%{cfg.buildcfg}/%{cfg.platform}"
OBJECT_DIR = "!$(SolutionDir)intermediates/$(Configuration)/$(Platform)/$(ProjectName)"

APP_INCLUDE_DIR = {}
ENGINE_INCLUDE_DIR = {}

workspace "NDREngine"
    startproject "Engine"
    configurations { "debug", "release" }
    platforms { "x64", "x86" }
    group "external"
        include "external/glad/glad.lua"
        include "external/glfw/glfw.lua"
        include "external/glm/glm.lua"
        include "external/stb_image/stb_image.lua"
        include "external/tiny_obj_loader/tiny_obj_loader.lua"
    group ""
    include "engine.lua"