#pragma once
#include "graphics/Shader.h"

namespace NDR
{
    class AssetManager
    {
    public:
        //TODO: make GetAssetRootPath() dynamic
        static std::string GetAssetRootPath();
        
        static Shader LoadShader(const std::string& assetPath);
    };
}
