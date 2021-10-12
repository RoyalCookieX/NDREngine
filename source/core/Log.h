#pragma once
#include "math/Transform.h"

namespace NDR
{
    static std::ostream& Format(std::ostream& os)
    {
        return os << std::fixed << std::setprecision(2);
    }
    
    static std::ostream& operator<<(std::ostream& os, const glm::vec2& vec2)
    {
        os << Format << "[" << vec2.x << ", " << vec2.y << "]";
        return os;
    }

    static std::ostream& operator<<(std::ostream& os, const glm::vec3& vec3)
    {
        os << Format << "[" << vec3.x << ", " << vec3.y << ", " << vec3.z << "]";
        return os;
    }

    static std::ostream& operator<<(std::ostream& os, const glm::vec4& vec4)
    {
        os << Format << "[" << vec4.x << ", " << vec4.y << ", " << vec4.z << ", " << vec4.w << "]";
        return os;
    }

    static std::ostream& operator<<(std::ostream& os, const glm::quat& quat)
    {
        os << Format << "[" << quat.x << ", " << quat.y << ", " << quat.z << ", " << quat.w << "]";
        return os;
    }

    static std::ostream& operator<<(std::ostream& os, const glm::mat4& mat4)
    {
        os << Format;
        os << "[" << mat4[0][0] << ", " << mat4[1][0] << ", " << mat4[2][0] << ", " << mat4[3][0] << "]" << std::endl;
        os << "[" << mat4[0][1] << ", " << mat4[1][1] << ", " << mat4[2][1] << ", " << mat4[3][1] << "]" << std::endl;
        os << "[" << mat4[0][2] << ", " << mat4[1][2] << ", " << mat4[2][2] << ", " << mat4[3][2] << "]" << std::endl;
        os << "[" << mat4[0][3] << ", " << mat4[1][3] << ", " << mat4[2][3] << ", " << mat4[3][3] << "]" << std::endl;
        return os;
    }

    static std::ostream& operator<<(std::ostream& os, const Transform& transform)
    {
        os << Format;
        os << "[Position: " << transform.GetPosition() <<
              " Rotation: " << glm::eulerAngles(transform.GetRotation()) <<
              " Scale: " << transform.GetScale() << "]";
        return os;
    }
}
