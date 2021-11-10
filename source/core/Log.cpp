#include "ndrpch.h"
#include "Log.h"

#if _MSC_VER
    #define DEBUGBREAK __debugbreak()
#else
    #define DEBUGBREAK
#endif

namespace NDR
{
    void LogMessage(LogLevel level, const char* format, ...)
    {        
        va_list args;
        va_start(args, format);

        const char* logLevels[5] { "[DEBUG] ", "[INFO] ", "[WARNING] ", "[ERROR] ", "[FATAL] " };
        //TODO: make levelMsg and message length dynamic
        char levelMsg[16384];
        char message[16384];
        std::memset(levelMsg, 0, sizeof(levelMsg));
        std::memset(message, 0, sizeof(message));
        
        sprintf_s(levelMsg, sizeof(levelMsg), "%s%s\n", logLevels[(int32_t)level], format);
        vsprintf_s(message, sizeof(message), levelMsg, args);
        PrintToConsole(level, message);
        
        va_end(args);
    }

    void AssertMessage(bool expression, const char* message, const char* file, int32_t line)
    {
        if(!expression)
        {
            NDR_LOGFATAL("%s | %s @ LINE %d", message, file, line);
            DEBUGBREAK;
        }           
    }
}