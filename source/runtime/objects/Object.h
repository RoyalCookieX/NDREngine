#pragma once
#include "runtime/components/Transform.h"

namespace NDR
{    
    class Object
    {
    public:
        Object();
        Object(const Transform& transform);
        Object(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale);
        virtual ~Object();

        Object(const Object& other);
        Object& operator=(const Object& other);

        Object(Object&& other) noexcept;
        Object& operator=(Object&& other) noexcept;

        Transform& GetTransform();
        glm::mat4 GetTransformMatrix() const;

        bool operator==(const Object& right);
        bool operator!=(const Object& right);
    private:
        Transform _transform;
    };
}
