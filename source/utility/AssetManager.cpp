#include "AssetManager.h"

#include <sstream>
#include <fstream>
#include <stb_image.h>

namespace NDR
{
    std::string AssetManager::GetAssetRootPath()
    {
        return "";
    }

    Shader AssetManager::LoadShader(const std::string& assetPath)
    {
        enum SHADERTYPE { NONE = -1, VERTEX = 0, FRAGMENT = 1 };
        SHADERTYPE type = NONE;
        
        std::string line;
        std::stringstream sources[2];
        std::ifstream filestream(GetAssetRootPath().append(assetPath));
        while(std::getline(filestream, line))
        {
            if(line.find("#shader vertex") != std::string::npos)
            {
                type = VERTEX;
            }
            else if(line.find("#shader fragment") != std::string::npos)
            {
                type = FRAGMENT;
            }
            else if(type != NONE)
            {
                sources[type] << line << std::endl;
            }
        }
        return Shader(sources[0].str().c_str(), sources[1].str().c_str());
    }

    Mesh AssetManager::LoadMesh(const std::string& assetPath)
    {
        std::string line;
        std::ifstream filestream(GetAssetRootPath().append(assetPath));
        while(std::getline(filestream, line))
        {
            
        }
        return Mesh({ }, { });
    }

    Texture AssetManager::LoadTexture(const std::string& assetPath)
    {
        int width, height, bpp;
        stbi_set_flip_vertically_on_load(1);
        unsigned char* buffer = stbi_load(assetPath.c_str(), &width, &height, &bpp, 4);
        return Texture(width, height, bpp, buffer);
    }
}
