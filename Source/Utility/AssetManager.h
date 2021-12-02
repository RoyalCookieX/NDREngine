#pragma once
#include "Defines.h"

namespace NDR
{
    class Shader;
    class Mesh;
    class Texture2D;
    class Texture2DAtlas;
    
    enum class AssetRoot
    {
        GAME, ENGINE
    };
        
    extern SPointer<Shader> LoadShader(const std::string& assetPath, AssetRoot root = AssetRoot::GAME);
    extern SPointer<Mesh> LoadMesh(const std::string& assetPath, AssetRoot root = AssetRoot::GAME);
    extern SPointer<Texture2D> LoadTexture2D(const std::string& assetPath, AssetRoot root = AssetRoot::GAME);
    extern SPointer<Texture2DAtlas> LoadTexture2DAtlas(const std::string& assetPath, UInt32 cellWidth, UInt32 cellHeight, AssetRoot root = AssetRoot::GAME);
}
