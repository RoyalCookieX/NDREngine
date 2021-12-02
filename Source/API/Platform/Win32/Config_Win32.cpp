#include "ndrpch.h"
#include "Core/Config.h"
#include "Core/Log.h"

namespace NDR
{
    static nlohmann::json LoadJSON(const std::string& filepath)
    {
        if(!std::filesystem::exists(filepath))
        {
            std::ofstream ofs(filepath);
            ofs << "{}";
        }
        
        std::ifstream ifs(filepath);
        nlohmann::json json;
        ifs >> json;
        return json;
    }

    static void SaveJSON(const std::string& filepath, nlohmann::json json)
    {
        std::ofstream ofs(filepath);
        ofs << std::setw(4) << json << std::endl;
    }
    
    bool Config::GetBool(const std::string& filepath, const std::string& section, const std::string& key)
    {
        auto json = LoadJSON(filepath);
        return json[section][key].get<bool>();
    }

    Int32 Config::GetInt(const std::string& filepath, const std::string& section, const std::string& key)
    {
        auto json = LoadJSON(filepath);
        return json[section][key].get<Int32>();
    }

    float Config::GetFloat(const std::string& filepath, const std::string& section, const std::string& key)
    {
        auto json = LoadJSON(filepath);
        return json[section][key].get<float>();
    }

    std::string Config::GetString(const std::string& filepath, const std::string& section, const std::string& key)
    {
        auto json = LoadJSON(filepath);
        return json[section][key].get<std::string>();
    }

    void Config::SetBool(const std::string& filepath, const std::string& section, const std::string& key, const bool value)
    {
        auto json = LoadJSON(filepath);
        json[section][key] = value;
        SaveJSON(filepath, json);
    }

    void Config::SetInt(const std::string& filepath, const std::string& section, const std::string& key, const Int32 value)
    {
        auto json = LoadJSON(filepath);
        json[section][key] = value;
        SaveJSON(filepath, json);
    }

    void Config::SetFloat(const std::string& filepath, const std::string& section, const std::string& key, const float value)
    {
        auto json = LoadJSON(filepath);
        json[section][key] = value;
        SaveJSON(filepath, json);
    }

    void Config::SetString(const std::string& filepath, const std::string& section, const std::string& key, const std::string& value)
    {
        auto json = LoadJSON(filepath);
        json[section][key] = value;
        SaveJSON(filepath, json);
    }
}
