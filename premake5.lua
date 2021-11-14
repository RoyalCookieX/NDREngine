workspace "NDREngine"
    startproject "Engine"
    configurations { "debug", "release" }
    platforms { "x64" }
    group "external"
        include "external/glad/glad.lua"
        include "external/glfw/glfw.lua"
        include "external/stb_image/stb_image.lua"
        include "external/tiny_obj_loader/tiny_obj_loader.lua"
    group ""
    include "engine.lua"