#pragma once

namespace NDR
{
    static std::vector<float> CreateQuad(
        const glm::mat4& mvp,
        const std::array<float, 8>& uvs,
        const glm::vec4& color = glm::vec4(1.0f),
        float texIndex = 0)
    {
        // get position of vertices
        const glm::vec4 v0 = mvp * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
        const glm::vec4 v1 = mvp * glm::vec4( 0.5f, -0.5f, 0.0f, 1.0f);
        const glm::vec4 v2 = mvp * glm::vec4( 0.5f,  0.5f, 0.0f, 1.0f);
        const glm::vec4 v3 = mvp * glm::vec4(-0.5f,  0.5f, 0.0f, 1.0f);

        return
        {
            v0.x, v0.y, v0.z, color.r, color.g, color.b, color.a, uvs[0], uvs[1], texIndex,
            v1.x, v1.y, v1.z, color.r, color.g, color.b, color.a, uvs[2], uvs[3], texIndex,
            v2.x, v2.y, v2.z, color.r, color.g, color.b, color.a, uvs[4], uvs[5], texIndex,
            v3.x, v3.y, v3.z, color.r, color.g, color.b, color.a, uvs[6], uvs[7], texIndex,
        };
    }
   
    static std::vector<float> CreateCube(
        const glm::mat4& mvp,
        const std::array<float, 8>& uvs,
        const glm::vec4& color = glm::vec4(1.0f),
        float texIndex = 0)
    {
        std::vector<float> vertices;
        //vertices.reserve(240);

        //std::vector<float> left = CreateQuad(, uvs);
        
        //vertices.insert(vertices.end(), left.begin(), left.end());
        
        return vertices;
    }
}