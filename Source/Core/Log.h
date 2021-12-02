#pragma once
#include "Defines.h"

#define NDR_DISABLE_FILELINE // disables the file and the line of the log.
// #define NDR_DISABLE_LOGDEBUG // disables debug logs.
// #define NDR_DISABLE_LOGINFO // disables info logs.
// #define NDR_DISABLE_LOGWARN // disables warning logs.

#if !defined(NDR_DISABLE_LOGDEBUG) && defined(NDR_DEBUG)
#define NDR_LOGDEBUG(message, ...) NDR::Log::LogMessage(__FILE__, __LINE__, NDR::LOGLEVEL_DEBUG, message, __VA_ARGS__)
#else
#define NDR_LOGDEBUG(message, ...)
#endif

#if !defined(NDR_DISABLE_LOGINFO)
#define NDR_LOGINFO(message, ...) NDR::Log::LogMessage(__FILE__, __LINE__, NDR::LOGLEVEL_INFO, message, __VA_ARGS__)
#else
#define NDR_LOGINFO(message, ...)
#endif

#if !defined(NDR_DISABLE_LOGWARN)
#define NDR_LOGWARN(message, ...) NDR::Log::LogMessage(__FILE__, __LINE__, NDR::LOGLEVEL_WARNING, message, __VA_ARGS__)
#else
#define NDR_LOGWARN(message, ...)
#endif

#define NDR_LOGERROR(message, ...) NDR::Log::LogMessage(__FILE__, __LINE__, NDR::LOGLEVEL_ERROR, message, __VA_ARGS__)
#define NDR_LOGFATAL(message, ...) NDR::Log::LogMessage(__FILE__, __LINE__, NDR::LOGLEVEL_FATAL, message, __VA_ARGS__); DEBUGBREAK

namespace NDR
{
    enum LogLevel
    {
        LOGLEVEL_DEBUG,
        LOGLEVEL_INFO,
        LOGLEVEL_WARNING,
        LOGLEVEL_ERROR,
        LOGLEVEL_FATAL
    };
    
    class Log
    {
    public:
        static void LogMessage(const char* file, Int32 line, LogLevel level, const char* message, ...);
        static void LogConsole(const char* message, Int32 color);
        static Int32 LogLevelToConsoleColor(LogLevel level);
    };
}
