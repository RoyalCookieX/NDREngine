#include "ndrpch.h"
#include "Object.h"

namespace NDR
{
    Object::Object() { }
    Object::Object(const Transform& transform): _transform(transform) { }
    Object::~Object() { }

    Object::Object(const Object& other): _transform(other._transform) { }
    Object& Object::operator=(const Object& other)
    {
        _transform = other._transform;
        return *this;
    }

    Object::Object(Object&& other) noexcept: _transform(std::move(_transform)) { }
    Object& Object::operator=(Object&& other) noexcept
    {
        if(*this != other)
            std::swap(_transform, other._transform);
        return *this;
    }

    Transform& Object::GetTransform() { return _transform; }
    const Transform& Object::GetTransform() const { return _transform; }
    glm::mat4 Object::GetTransformMatrix() const { return _transform.GetMatrix(); }

    bool Object::operator==(const Object& right) { return this == &right; }
    bool Object::operator!=(const Object& right) { return !(this == &right); }
}
