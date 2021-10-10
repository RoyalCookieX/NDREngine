#pragma once
#include "graphics/Mesh.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"

namespace NDR
{
    //TODO: make GetAssetRootPath() dynamic
    extern std::string GetAssetRootPath();
        
    extern Shader LoadShader(const std::string& assetPath);
    extern Mesh LoadMesh(const std::string& assetPath);
    extern Texture2D LoadTexture2D(const std::string& assetPath);
    extern Texture2DAtlas LoadTexture2DAtlas(const std::string& assetPath, uint32_t cellWidth, uint32_t cellHeight);
}
