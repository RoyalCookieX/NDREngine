workspace "NDREngine"
    startproject "Engine"
    configurations { "Debug", "Release" }
    platforms { "x64" }
    group "External"
        include "External/glad/glad.lua"
        include "External/glfw/glfw.lua"
        include "External/stb_image/stb_image.lua"
        include "External/tiny_obj_loader/tiny_obj_loader.lua"
    group ""
    include "Engine.lua"