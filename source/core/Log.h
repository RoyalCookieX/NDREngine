#pragma once
#include <iostream>
#include "math/Transform.h"

namespace NDR
{
    inline std::ostream& operator<<(std::ostream& os, const glm::vec2& vec2)
    {
        os << "[" << vec2.x << ", " << vec2.y << "]";
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, const glm::vec3& vec3)
    {
        os << "[" << vec3.x << ", " << vec3.y << ", " << vec3.z << "]";
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, const glm::vec4& vec4)
    {
        os << "[" << vec4.x << ", " << vec4.y << ", " << vec4.z << ", " << vec4.w << "]";
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, const glm::quat& quat)
    {
        os << "[" << quat.x << ", " << quat.y << ", " << quat.z << ", " << quat.w << "]";
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, const glm::mat4& mat4)
    {
        os << "[" << mat4[0][0] << ", " << mat4[1][0] << ", " << mat4[2][0] << ", " << mat4[3][0] << "]" << std::endl;
        os << "[" << mat4[0][1] << ", " << mat4[1][1] << ", " << mat4[2][1] << ", " << mat4[3][1] << "]" << std::endl;
        os << "[" << mat4[0][2] << ", " << mat4[1][2] << ", " << mat4[2][2] << ", " << mat4[3][2] << "]" << std::endl;
        os << "[" << mat4[0][3] << ", " << mat4[1][3] << ", " << mat4[2][3] << ", " << mat4[3][3] << "]";
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, const Transform& transform)
    {
        os << "[Position: " << transform.GetPosition() << " Rotation: " << transform.GetRotation() << " Scale: " << transform.GetScale() << "]";
        return os;
    }
}
