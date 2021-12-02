#include "ndrpch.h"
#include "Log.h"

namespace NDR
{
    void Log::LogMessage(const char* file, Int32 line, LogLevel level, const char* message, ...)
    {
        // get message string
        va_list args;
        va_start(args, message);
        const char* levelStrings[] { "[DEBUG]:   ", "[INFO]:    ", "[WARNING]: ", "[ERROR]:   ", "[FATAL]:   " };
        const char* levelStr = levelStrings[(Int32)level];

        std::stringstream ss;
        ss << levelStr << message << std::endl;
#if !defined(NDR_DISABLE_FILELINE)
        ss << file << " @ LINE " << line << std::endl;
#endif
        char buffer[32000] = "";
        vsprintf_s(buffer, sizeof(buffer), ss.str().c_str(), args);
        
        // get console color
        const Int32 consoleColor = LogLevelToConsoleColor(level);

        // output to console
        LogConsole(buffer, consoleColor);
    }

}