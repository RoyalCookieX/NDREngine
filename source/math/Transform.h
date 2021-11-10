#pragma once

#define VEC3_ZERO glm::vec3(0.0f)
#define VEC3_ONE glm::vec3(1.0f)
#define VEC3_RIGHT glm::vec3(1.0f, 0.0f, 0.0f)
#define VEC3_UP glm::vec3(0.0f, 1.0f, 0.0f)
#define VEC3_FORWARD glm::vec3(0.0f, 0.0f, 1.0f)

#define QUAT_IDENTITY glm::identity<glm::quat>()

#define MAT4_IDENTITY glm::mat4(1.0f)

namespace NDR
{
    enum class TransformSpace { WORLD, LOCAL };
    
    struct Transform
    {
    public:
        Transform();
        Transform(const glm::mat4& matrix);
        Transform(const glm::vec3& position);
        Transform(const glm::vec3& position, const glm::vec3& eulerDeg);
        Transform(const glm::vec3& position, const glm::vec3& eulerDeg, const glm::vec3& scale);
        
        glm::mat4 GetMatrix() const;
        glm::vec3 GetPosition(TransformSpace space = TransformSpace::WORLD) const;
        glm::quat GetRotation(TransformSpace space = TransformSpace::WORLD) const;
        glm::vec3 GetScale(TransformSpace space = TransformSpace::WORLD) const;

        Transform& SetPosition(const glm::vec3& position, TransformSpace space = TransformSpace::LOCAL);
        Transform& SetRotation(const glm::vec3& eulerDeg, TransformSpace space = TransformSpace::LOCAL);
        Transform& SetScale(const glm::vec3& scale);

        Transform& Translate(const glm::vec3& translation, TransformSpace space = TransformSpace::LOCAL);
        Transform& Rotate(const glm::vec3& eulerDeg, TransformSpace space = TransformSpace::LOCAL);
        Transform& Rotate(float degrees, const glm::vec3& axis, TransformSpace = TransformSpace::LOCAL);
        Transform& Scale(const glm::vec3& scalar);

        glm::vec3 GetRight() const;
        glm::vec3 GetUp() const;
        glm::vec3 GetForward() const;
    private:
        std::tuple<glm::vec3, glm::quat, glm::vec3> Decompose() const;
        
        glm::mat4 _matrix;
    };
}
