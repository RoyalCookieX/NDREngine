#include "ndrpch.h"
#include "AssetManager.h"
#include "core/Config.h"
#include "core/Log.h"

namespace tinyobj
{
    bool operator==(const index_t& left, const index_t& right)
    {
        return
        left.vertex_index == right.vertex_index &&
        left.texcoord_index == right.texcoord_index &&
        left.normal_index == right.normal_index;
    }
}

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

    // From https://github.com/tinyobjloader/tinyobjloader
    Mesh LoadMesh(const std::string& assetPath, AssetRoot root)
    {
        // parse .obj file and check for warnings/errors
        tinyobj::ObjReaderConfig readerConfig;
        readerConfig.mtl_search_path = "./";
        readerConfig.triangulate = true;
        
        tinyobj::ObjReader reader;
        if(!reader.ParseFromFile(GetAssetRootPath(assetPath, root), readerConfig))
        {
            if(!reader.Error().empty())
                NDR_LOGERROR("[AssetManager]: %s", reader.Error());
            if(!reader.Warning().empty())
                NDR_LOGWARN("[AssetManager]: %s", reader.Warning());
            return {};
        }

        const tinyobj::attrib_t& assetAttributes = reader.GetAttrib();
        const std::vector<tinyobj::shape_t>& assetShapes = reader.GetShapes();
        const std::vector<tinyobj::material_t>& assetMaterials = reader.GetMaterials();
        std::vector<tinyobj::index_t> meshIndexCache;

        VertexLayout layout;
        layout.AddAttribute({3, false}); // position
        layout.AddAttribute({2, false}); // tex coords
        layout.AddAttribute({3, false}); // normals
        std::vector<float> vertices;
        std::vector<SubMesh> subMeshes;

        const bool hasTexCoords = assetAttributes.texcoords.size() > 0;
        const bool hasNormals = assetAttributes.normals.size() > 0;
        for(size_t shapeIndex = 0; shapeIndex < assetShapes.size(); shapeIndex++)
        {
            size_t indexOffset = 0;
            const tinyobj::mesh_t& mesh = assetShapes[shapeIndex].mesh;

            std::vector<uint32_t> indices;
            
            for(size_t faceIndex = 0; faceIndex < mesh.num_face_vertices.size(); faceIndex++)
            {
                size_t verticesPerFace = (size_t)mesh.num_face_vertices[faceIndex];
                for(size_t vertexIndex = 0; vertexIndex < verticesPerFace; vertexIndex++)
                {
                    const tinyobj::index_t vertexAttributeIndex = mesh.indices[indexOffset + vertexIndex];
                    const auto& indexLocation = std::find(meshIndexCache.begin(), meshIndexCache.end(), vertexAttributeIndex);
                    if(indexLocation == meshIndexCache.end())
                    {
                        // add new vertex to vertexBuffer
                        size_t posIndex = 3 * (size_t)vertexAttributeIndex.vertex_index;
                        size_t texIndex = 2 * (size_t)vertexAttributeIndex.texcoord_index * hasTexCoords;
                        size_t nmlIndex = 3 * (size_t)vertexAttributeIndex.normal_index * hasNormals;
                    
                        // position
                        vertices.push_back(assetAttributes.vertices[posIndex + 0]);
                        vertices.push_back(assetAttributes.vertices[posIndex + 1]);
                        vertices.push_back(assetAttributes.vertices[posIndex + 2]);

                        // tex coords
                        if(hasTexCoords)
                        {
                            vertices.push_back(assetAttributes.texcoords[texIndex + 0]);
                            vertices.push_back(assetAttributes.texcoords[texIndex + 1]);
                        }
                        else
                        {
                            vertices.push_back(0.0f);
                            vertices.push_back(0.0f);
                        }

                        // normals
                        if(hasNormals)
                        {
                            vertices.push_back(assetAttributes.normals[nmlIndex + 0]);
                            vertices.push_back(assetAttributes.normals[nmlIndex + 1]);
                            vertices.push_back(assetAttributes.normals[nmlIndex + 2]);
                        }
                        else
                        {
                            vertices.push_back(0.0f);
                            vertices.push_back(0.0f);
                            vertices.push_back(0.0f);
                        }
                        // add new indices to indexBuffer & update cache
                        indices.push_back((uint32_t)meshIndexCache.size());
                        meshIndexCache.push_back(vertexAttributeIndex);
                    }
                    else
                    {
                        // vertex is already defined, add that index to indexBuffer
                        indices.push_back((uint32_t)std::distance(meshIndexCache.begin(), indexLocation));
                    }
                }
                indexOffset += verticesPerFace;
            }
            NDR_LOGDEBUG("Index Buffer Count: %d", indices.size());
            IndexBuffer indexBuffer(indices);
            Material material(LoadShader("assets/shaders/Mesh.shader", AssetRoot::ENGINE),
                         ENABLECULLING | CULLBACK | ENABLEBLENDING | TRANSPARENT);
            subMeshes.emplace_back(std::move(indexBuffer), std::move(material));
        }
        NDR_LOGDEBUG("Vertex Buffer Count: %d", vertices.size());
        VertexBuffer vertexBuffer(vertices, layout);
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
