#pragma once
#include "math/Transform.h"

namespace NDR
{    
    class Object
    {
    public:
        Object();
        Object(const Transform& transform);
        virtual ~Object();

        Object(const Object& other);
        Object& operator=(const Object& other);

        Object(Object&& other) noexcept;
        Object& operator=(Object&& other) noexcept;

        virtual void Tick() { }

        Transform& GetTransform();
        const Transform& Object::GetTransform() const;
        glm::mat4 GetTransformMatrix() const;

        bool operator==(const Object& right);
        bool operator!=(const Object& right);
    private:
        Transform _transform;
    };
}
