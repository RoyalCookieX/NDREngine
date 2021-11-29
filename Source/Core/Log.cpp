#include "ndrpch.h"
#include "Log.h"

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
        
        sprintf_s(levelMsg, sizeof(levelMsg), "%s%s\n", logLevels[(Int32)level], format);
        vsprintf_s(message, sizeof(message), levelMsg, args);
        PrintToConsole(level, message);
        
        va_end(args);
    }
}