#pragma once
#include "Defines.h"

#define NDR_ENGINE_CONFIG_PATH "Config/Engine.json"
#define NDR_APP_CONFIG_PATH "Config/Application.json"

namespace NDR
{
    class Config
    {
    public:
        static bool GetBool(const std::string& filepath, const std::string& section, const std::string& key);
        static Int32 GetInt(const std::string& filepath, const std::string& section, const std::string& key);
        static float GetFloat(const std::string& filepath, const std::string& section, const std::string& key);
        static std::string GetString(const std::string& filepath, const std::string& section, const std::string& key);

        static void SetBool(const std::string& filepath, const std::string& section, const std::string& key, bool value);
        static void SetInt(const std::string& filepath, const std::string& section, const std::string& key, Int32 value);
        static void SetFloat(const std::string& filepath, const std::string& section, const std::string& key, float value);
        static void SetString(const std::string& filepath, const std::string& section, const std::string& key, const std::string& value);
    };
}