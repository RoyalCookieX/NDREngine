#pragma once
#include "graphics/Mesh.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"

namespace NDR
{
    enum class AssetRoot
    {
        GAME, ENGINE
    };
        
    extern Shader LoadShader(const std::string& assetPath, AssetRoot root = AssetRoot::GAME);
    // TODO: Load Meshes from filepath
    // extern Mesh LoadMesh(const std::string& assetPath, AssetRoot root = AssetRoot::GAME);
    extern Texture2D LoadTexture2D(const std::string& assetPath, AssetRoot root = AssetRoot::GAME);
    extern Texture2DAtlas LoadTexture2DAtlas(const std::string& assetPath, uint32_t cellWidth, uint32_t cellHeight, AssetRoot root = AssetRoot::GAME);
}
