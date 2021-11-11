#pragma once
#include "math/Transform.h"

#if NDR_DEBUG
#define NDR_LOGDEBUG(message, ...) NDR::LogMessage(NDR::LogLevel::NDRDEBUG, message, __VA_ARGS__)
#else
#define NDR_LOGDEBUG()
#endif
#define NDR_LOGINFO(message, ...) NDR::LogMessage(NDR::LogLevel::NDRINFO, message, __VA_ARGS__)
#define NDR_LOGWARN(message, ...) NDR::LogMessage(NDR::LogLevel::NDRWARN, message, __VA_ARGS__)
#define NDR_LOGERROR(message, ...) NDR::LogMessage(NDR::LogLevel::NDRERROR, message, __VA_ARGS__)
#define NDR_LOGFATAL(message, ...) NDR::LogMessage(NDR::LogLevel::NDRFATAL, message, __VA_ARGS__)

namespace NDR
{
    enum class LogLevel
    {
        NDRDEBUG = 0,
        NDRINFO = 1,
        NDRWARN = 2,
        NDRERROR = 3,
        NDRFATAL = 4
    };
    
    extern void LogMessage(LogLevel level, const char* format, ...);
    extern void PrintToConsole(LogLevel level, const char* message);
    
    inline std::ostream& Format(std::ostream& os)
    {
        return os << std::fixed << std::setprecision(2);
    }
    
    inline std::ostream& operator<<(std::ostream& os, const glm::vec2& vec2)
    {
        os << Format << "[" << vec2.x << ", " << vec2.y << "]";
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, const glm::vec3& vec3)
    {
        os << Format << "[" << vec3.x << ", " << vec3.y << ", " << vec3.z << "]";
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, const glm::vec4& vec4)
    {
        os << Format << "[" << vec4.x << ", " << vec4.y << ", " << vec4.z << ", " << vec4.w << "]";
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, const glm::quat& quat)
    {
        os << Format << "[" << quat.x << ", " << quat.y << ", " << quat.z << ", " << quat.w << "]";
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, const glm::mat4& mat4)
    {
        os << Format;
        os << "[" << mat4[0][0] << ", " << mat4[1][0] << ", " << mat4[2][0] << ", " << mat4[3][0] << "]" << std::endl;
        os << "[" << mat4[0][1] << ", " << mat4[1][1] << ", " << mat4[2][1] << ", " << mat4[3][1] << "]" << std::endl;
        os << "[" << mat4[0][2] << ", " << mat4[1][2] << ", " << mat4[2][2] << ", " << mat4[3][2] << "]" << std::endl;
        os << "[" << mat4[0][3] << ", " << mat4[1][3] << ", " << mat4[2][3] << ", " << mat4[3][3] << "]" << std::endl;
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, const Transform& transform)
    {
        os << Format;
        os << "[Position: " << transform.GetPosition() <<
              " Rotation: " << glm::eulerAngles(transform.GetRotation()) <<
              " Scale: " << transform.GetScale() << "]";
        return os;
    }
}
