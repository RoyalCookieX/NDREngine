TARGET_DIR = "%{wks.location}/binaries/%{cfg.buildcfg}/%{cfg.platform}"
OBJECT_DIR = "!$(SolutionDir)/intermediates/$(Configuration)/$(Platform)/$(ProjectName)"
PROJECT_LOC = "%{wks.location}/projfiles/"

INCLUDE_DIR = {}

workspace "NDREngine"
    startproject "Engine"
    configurations { "debug", "release" }
    platforms { "x64" }
    group "External"
        include "external/glad/glad.lua"
        include "external/glfw/glfw.lua"
        include "external/glm/glm.lua"
    group ""
    include "engine.lua"