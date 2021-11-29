local m = {}

function m.build()
    include "Defines"

    -- create folder structure
    os.mkdir("Assets")
    os.mkdir("Config")
    os.mkdir("Source")

    newoption {
        trigger = "projectname",
        description = "The name of the Project",
        default = ""
    }

    newoption {
        trigger = "enginepath",
        description = "The path to NDREngine",
        default = ""
    }

    REQUIRED_VARS = 
    { 
        ["Project Name"] = _OPTIONS["projectname"], 
        ["Engine Path"] = _OPTIONS["enginepath"]
    }

    ENGINE_PATH = REQUIRED_VARS["Engine Path"]
    PROJECT_NAME = REQUIRED_VARS["Project Name"]

    defaultColor = term.getTextColor()
    for name, value in pairs(REQUIRED_VARS) do
        if(value == "") then
            term.setTextColor(term.red)
            print("[Premake]: " .. name .. " is not set!")
            term.setTextColor(defaultColor)
            os.exit()
        end
    end

    -- Creeate Config File
    ENGINE_CONFIG_PATH = "Config/Engine.json"

    JSON_OBJ = {["Core"]={}}
    JSON_STR = io.readfile(ENGINE_CONFIG_PATH)
    if JSON_STR == nil or JSON_STR == "" then
        JSON_OBJ["Core"]["EnginePath"] = ENGINE_PATH
    else
        JSON_OBJ, ERR = json.decode(JSON_STR)
    end

    JSON_OBJ["Core"]["EnginePath"] = ENGINE_PATH

    JSON_STR, ERR = json.encode(JSON_OBJ)
    io.writefile(ENGINE_CONFIG_PATH, JSON_STR)

    -- Create Project
    workspace (PROJECT_NAME)
        startproject (PROJECT_NAME)
        configurations { "Debug", "Release" }
        platforms { "x64" }
        group "Engine/External"
            includeexternal (REQUIRED_VARS["Engine Path"] .. "/External/glfw/glfw.lua")
            includeexternal (REQUIRED_VARS["Engine Path"] .. "/External/glad/glad.lua")
            includeexternal (REQUIRED_VARS["Engine Path"] .. "/External/stb_image/stb_image.lua")
            includeexternal (REQUIRED_VARS["Engine Path"] .. "/External/tiny_obj_loader/tiny_obj_loader.lua")
        group "Engine"
            includeexternal (ENGINE_PATH .. "/Engine.lua")
        group "Game"
    project (PROJECT_NAME)
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        systemversion "latest"
        staticruntime "On"
        targetdir (TARGET_DIR)
        objdir (OBJECT_DIR)
        files
        {
            "Assets/**",
            "Source/**.h", "Source/**.cpp"
        }
        includedirs
        {
            "Source",
            (ENGINE_PATH .. "/Source"),
            (ENGINE_PATH .. "/External/glm/include")
        }
        links
        {
            "Engine"
        }
        filter "platforms:x64"
            architecture "x64"
        filter "system:windows"
            defines "NDR_PLATFORM_WINDOWS"
        filter "configurations:Debug"
            defines "NDR_DEBUG"
            runtime "Debug"
            symbols "On"
        filter "configurations:Release"
            defines "NDR_RELEASE"
            runtime "Release"
            optimize "On"
end

return m