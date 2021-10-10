#pragma once
#include "graphics/Mesh.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"

namespace NDR
{
    class AssetManager
    {
    public:
        //TODO: make GetAssetRootPath() dynamic
        static std::string GetAssetRootPath();
        
        static Shader LoadShader(const std::string& assetPath);
        static Mesh LoadMesh(const std::string& assetPath);
        static Texture2D LoadTexture2D(const std::string& assetPath);
    };
}
