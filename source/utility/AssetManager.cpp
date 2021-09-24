#include "ndrpch.h"
#include "AssetManager.h"

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
        tinyobj::attrib_t attributes;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string errorMsg;

        if(!tinyobj::LoadObj(&attributes, &shapes, &materials, &errorMsg, GetAssetRootPath().append(assetPath).c_str()))
        {
            std::cout << "[Tiny OBJ Loader Error]: " << errorMsg;
            return Mesh({});
        }
        
        tinyobj::mesh_t mesh = shapes[0].mesh;
        std::unordered_set<uint32_t> indexCache;
        VertexLayout layout;
        layout
        .AddAttribute({3, false})  // position
        .AddAttribute({2, false})  // tex coords
        .AddAttribute({3, false}); // normals
        std::vector<float> verts;
        std::vector<uint32_t> indices;

        for(int i = 0; i < mesh.indices.size(); i++)
        {
            tinyobj::index_t index = mesh.indices[i];
            const int posIndex = index.vertex_index;
            const int texIndex = index.texcoord_index;
            const int nmlIndex = index.normal_index;

            verts.push_back(attributes.vertices[posIndex * 3 + 0]);
            verts.push_back(attributes.vertices[posIndex * 3 + 1]);
            verts.push_back(attributes.vertices[posIndex * 3 + 2]);

            verts.push_back(attributes.texcoords[texIndex * 2 + 0]);
            verts.push_back(attributes.texcoords[texIndex * 2 + 1]);

            verts.push_back(attributes.normals[nmlIndex * 3 + 0]);
            verts.push_back(attributes.normals[nmlIndex * 3 + 1]);
            verts.push_back(attributes.normals[nmlIndex * 3 + 2]);
        }
        
        return Mesh(VertexData(verts), IndexData(indices), layout);
    }

    Texture AssetManager::LoadTexture(const std::string& assetPath)
    {
        int width, height, bpp;
        stbi_set_flip_vertically_on_load(1);
        unsigned char* buffer = stbi_load(assetPath.c_str(), &width, &height, &bpp, 4);
        return Texture(width, height, bpp, buffer);
    }
}
