#include "ndrpch.h"
#include "Log.h"

#if _MSC_VER
    #define DEBUGBREAK __debugbreak()
#else
    #define DEBUGBREAK
#endif

//TODO: Add Platform Specific Logging to terminal

namespace NDR
{
    void LogMessage(LogType logType, const char* format, ...)
    {        
        va_list args;
        va_start(args, format);

        const char* logLevels[5] { "[DEBUG] ", "[INFO] ", "[WARNING] ", "[ERROR] ", "[FATAL] " };
        char buffer[32768];
        std::memset(buffer, 0, sizeof(buffer));
        sprintf_s(buffer, sizeof(buffer), "%s%s\n", logLevels[(int32_t)logType], format);
        vprintf_s(buffer, args);
        
        va_end(args);
    }

    void AssertMessage(bool expression, const char* message, const char* file, int32_t line)
    {
        if(!expression)
        {
            LogMessage(LogType::FATAL, "%s | %s @ LINE %d", message, file, line);
            DEBUGBREAK;
        }           
    }
}