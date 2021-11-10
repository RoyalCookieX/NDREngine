#include <ndrpch.h>
#include "core/Config.h"

namespace NDR
{
    static std::map<std::string, mINI::INIStructure> configCache;

    static mINI::INIStructure GetConfig(const std::string& filepath)
    {
        if(configCache.find(filepath) != configCache.end())
            return configCache[filepath];

        const mINI::INIFile configFile(filepath);
        mINI::INIStructure config;
        if(configFile.read(config))
        {
            configCache.insert(std::make_pair(filepath, config));
            return config;           
        }
        perror("[Config Error]: Config file does not exist!\n");
        return {};
    }

    static void SetConfig(const std::string& filepath, mINI::INIStructure& config)
    {
        if(configCache.find(filepath) != configCache.end())
            configCache[filepath] = config;
        
        const mINI::INIFile configFile(filepath);
        configFile.write(config, true);
    }
    
    bool Config::GetBool(const std::string& filepath, const std::string& section, const std::string& key)
    {
        auto config = GetConfig(filepath);
        std::istringstream iss(config[section][key]);
        bool value;
        iss >> std::boolalpha >> value;
        return value;
    }

    int32_t Config::GetInt(const std::string& filepath, const std::string& section, const std::string& key)
    {
        auto config = GetConfig(filepath);
        std::istringstream iss(config[section][key]);
        int32_t value;
        iss >> value;
        return value;
    }

    float Config::GetFloat(const std::string& filepath, const std::string& section, const std::string& key)
    {
        auto config = GetConfig(filepath);
        std::istringstream iss(config[section][key]);
        float value;
        iss >> value;
        return value;
    }

    std::string Config::GetString(const std::string& filepath, const std::string& section, const std::string& key)
    {
        auto config = GetConfig(filepath);
        return config[section][key];
    }

    void Config::SetBool(const std::string& filepath, const std::string& section, const std::string& key, const bool value)
    {
        auto config = GetConfig(filepath);
        config[section][key] = value ? "true" : "false";
        SetConfig(filepath, config);
    }

    void Config::SetInt(const std::string& filepath, const std::string& section, const std::string& key, const int32_t value)
    {
        auto config = GetConfig(filepath);
        config[section][key] = std::to_string(value);
        SetConfig(filepath, config);
    }

    void Config::SetFloat(const std::string& filepath, const std::string& section, const std::string& key, const float value)
    {
        auto config = GetConfig(filepath);
        config[section][key] = std::to_string(value);
        SetConfig(filepath, config);
    }

    void Config::SetString(const std::string& filepath, const std::string& section, const std::string& key, const std::string& value)
    {
        auto config = GetConfig(filepath);
        config[section][key] = value;
        SetConfig(filepath, config);
    }
}
