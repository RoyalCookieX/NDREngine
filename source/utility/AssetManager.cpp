#include "ndrpch.h"
#include "AssetManager.h"
#include "core/Config.h"

namespace NDR
{
    std::string GetAssetRootPath(const std::string& assetPath, AssetRoot root)
    {
        std::stringstream ss;
        switch(root)
        {
            default:
            case AssetRoot::GAME: break;
            case AssetRoot::ENGINE: ss << Config::GetString(NDR_ENGINE_CONFIG_PATH, "Core", "EnginePath") << "/"; break;
        }
        ss << assetPath;
        return ss.str();
    }

    Shader LoadShader(const std::string& assetPath, AssetRoot root)
    {
        int index = -1;
        std::string line;
        std::stringstream sources[2];
        std::ifstream filestream(GetAssetRootPath(assetPath, root));
        
        while(std::getline(filestream, line))
        {
            if(line.find("#vertex") != std::string::npos)
                index = VERTEX;
            else if(line.find("#fragment") != std::string::npos)
                index = FRAGMENT;
            else if(line.find("#compute") != std::string::npos)
                index = COMPUTE;
            else if(line.find("#geometry") != std::string::npos)
                index = GEOMETRY;
            else if(index != -1)
                sources[index] << line << std::endl;
        }
        return Shader(sources[0].str(), sources[1].str());
    }

    // Mesh LoadMesh(const std::string& assetPath, AssetRoot root)
    // {
    //     tinyobj::attrib_t attributes;
    //     std::vector<tinyobj::shape_t> shapes;
    //     std::vector<tinyobj::material_t> materials;
    //     std::string errorMsg;
    //
    //     if(!tinyobj::LoadObj(&attributes, &shapes, &materials, &errorMsg, GetAssetRootPath(assetPath, root).c_str()))
    //     {
    //         std::cout << "[Tiny OBJ Loader Error]: " << errorMsg;
    //         return Mesh();
    //     }
    //     
    //     tinyobj::mesh_t mesh = shapes[0].mesh;
    //     std::unordered_set<uint32_t> indexCache;
    //     std::vector<float> verts;
    //     std::vector<uint32_t> indices;
    //
    //     for(uint32_t i = 0; i < mesh.indices.size(); i++)
    //     {
    //         tinyobj::index_t index = mesh.indices[i];
    //         const int posIndex = index.vertex_index;
    //         const int texIndex = index.texcoord_index;
    //         const int nmlIndex = index.normal_index;
    //
    //         verts.push_back(attributes.vertices[posIndex * 3 + 0]);
    //         verts.push_back(attributes.vertices[posIndex * 3 + 1]);
    //         verts.push_back(attributes.vertices[posIndex * 3 + 2]);
    //
    //         verts.push_back(attributes.texcoords[texIndex * 2 + 0]);
    //         verts.push_back(attributes.texcoords[texIndex * 2 + 1]);
    //
    //         verts.push_back(attributes.normals[nmlIndex * 3 + 0]);
    //         verts.push_back(attributes.normals[nmlIndex * 3 + 1]);
    //         verts.push_back(attributes.normals[nmlIndex * 3 + 2]);
    //     }
    //
    //     VertexLayout layout;
    //     layout
    //     .AddAttribute({3, false})  // position
    //     .AddAttribute({2, false})  // tex coords
    //     .AddAttribute({3, false}); // normals
    //     VertexBuffer vb(verts, layout);
    //     IndexBuffer ib(indices);
    //     VertexArray vertexArray(std::move(vb), std::move(ib));        
    //
    //     return Mesh(std::move(vertexArray), LoadShader("assets/shaders/Cube.shader"));
    // }

    Texture2D LoadTexture2D(const std::string& assetPath, AssetRoot root)
    {
        int width, height, bpp;
        stbi_set_flip_vertically_on_load(1);
        unsigned char* buffer = stbi_load(GetAssetRootPath(assetPath, root).c_str(), &width, &height, &bpp, 4);
        return Texture2D({width, height, bpp}, buffer);
    }

    Texture2DAtlas LoadTexture2DAtlas(const std::string& assetPath, uint32_t cellWidth, uint32_t cellHeight, AssetRoot root)
    {
        int width, height, bpp;
        stbi_set_flip_vertically_on_load(1);
        unsigned char* buffer = stbi_load(GetAssetRootPath(assetPath, root).c_str(), &width, &height, &bpp, 4);
        return Texture2DAtlas({width, height, cellWidth, cellHeight, bpp}, buffer);
    }
}
