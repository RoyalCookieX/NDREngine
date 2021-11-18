#include "ndrpch.h"
#include "AssetManager.h"
#include "core/Config.h"
#include "core/Log.h"

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

    //TODO: Move this somewhere else
    struct MeshIndex
    {
    public:
        MeshIndex(int32_t posIndex, int32_t texIndex, int32_t nmlIndex):
            posIndex(posIndex),
            texIndex(texIndex),
            nmlIndex(nmlIndex)
        {
        }
        bool operator==(const MeshIndex& other) const
        {
            return
            posIndex == other.posIndex &&
            texIndex == other.texIndex &&
            nmlIndex == other.nmlIndex;
        }

        int32_t posIndex, texIndex, nmlIndex;
    };

    Mesh LoadMesh(const std::string& assetPath, AssetRoot root)
    {
        tinyobj::attrib_t attributes;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string errorMsg;
    
        if(!tinyobj::LoadObj(&attributes, &shapes, &materials, &errorMsg, GetAssetRootPath(assetPath, root).c_str()))
        {
            NDR_LOGERROR("[AssetManager]: %s", errorMsg.c_str());
            return Mesh();
        }

        VertexLayout layout;
        layout.AddAttribute({3, false}); // position
        layout.AddAttribute({2, false}); // tex coords
        layout.AddAttribute({3, false}); // normals
        std::vector<float> verts;
        std::vector<SubMesh> subMeshes;
        std::vector<MeshIndex> indexCache;
        
        for (auto shape : shapes)
        {
            tinyobj::mesh_t mesh = shape.mesh;
            std::vector<uint32_t> indices;
    
            for(uint32_t i = 0; i < mesh.indices.size(); i++)
            {
                MeshIndex meshIndex(
                    mesh.indices[i].vertex_index,
                    mesh.indices[i].texcoord_index,
                    mesh.indices[i].normal_index);

                auto indexLocation = std::find(indexCache.begin(), indexCache.end(), meshIndex);
                if(indexLocation != indexCache.end())
                {
                    indices.push_back((uint32_t)std::distance(indexCache.begin(), indexLocation));
                }
                else
                {
                    const int32_t posIndex = meshIndex.posIndex;
                    const int32_t texIndex = meshIndex.texIndex;
                    const int32_t nmlIndex = meshIndex.nmlIndex;

                    if(posIndex > -1)
                    {
                        verts.push_back(attributes.vertices[posIndex * 3 + 0]);
                        verts.push_back(attributes.vertices[posIndex * 3 + 1]);
                        verts.push_back(attributes.vertices[posIndex * 3 + 2]);                
                    }
                    else
                    {
                        verts.push_back(0.0f);
                        verts.push_back(0.0f);
                        verts.push_back(0.0f);
                    }

                    if(texIndex > -1)
                    {
                        verts.push_back(attributes.texcoords[texIndex * 2 + 0]);
                        verts.push_back(attributes.texcoords[texIndex * 2 + 1]);             
                    }
                    else
                    {
                        verts.push_back(0.0f);
                        verts.push_back(0.0f);
                    }

                    if(nmlIndex > -1)
                    {
                        verts.push_back(attributes.normals[nmlIndex * 3 + 0]);
                        verts.push_back(attributes.normals[nmlIndex * 3 + 1]);
                        verts.push_back(attributes.normals[nmlIndex * 3 + 2]);
                    }
                    else
                    {
                        verts.push_back(0.0f);
                        verts.push_back(0.0f);
                        verts.push_back(0.0f);
                    }
                    
                    indexCache.push_back(MeshIndex(posIndex, texIndex, nmlIndex));
                    indices.push_back((uint32_t)indexCache.size() - 1);
                }
            }

            IndexBuffer indexBuffer(indices);
            subMeshes.emplace_back(std::move(indexBuffer), LoadShader("assets/shaders/Mesh.shader", AssetRoot::ENGINE));
        }
        NDR_LOGDEBUG("[AssetManager]:\n - Vertex Buffer: %d\n - Total Vertices: %d\n - Total Indices: %d",
            verts.size(),
            verts.size() / layout.GetAttributeComponentCount(),
            indexCache.size());
        
        VertexBuffer vertexBuffer(verts, layout);
        return Mesh(std::move(vertexBuffer), std::move(subMeshes));
    }

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
