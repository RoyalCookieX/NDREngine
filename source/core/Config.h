#pragma once

#define NDR_ENGINE_CONFIG_PATH "cache/engine.ini"
#define NDR_GAME_CONFIG_PATH "cache/game.ini"

namespace NDR
{
    class Config
    {
    public:
        static bool GetBool(const std::string& filepath, const std::string& section, const std::string& key);
        static int32_t GetInt(const std::string& filepath, const std::string& section, const std::string& key);
        static float GetFloat(const std::string& filepath, const std::string& section, const std::string& key);
        static std::string GetString(const std::string& filepath, const std::string& section, const std::string& key);

        static void SetBool(const std::string& filepath, const std::string& section, const std::string& key, bool value);
        static void SetInt(const std::string& filepath, const std::string& section, const std::string& key, int32_t value);
        static void SetFloat(const std::string& filepath, const std::string& section, const std::string& key, float value);
        static void SetString(const std::string& filepath, const std::string& section, const std::string& key, const std::string& value);
    };
}