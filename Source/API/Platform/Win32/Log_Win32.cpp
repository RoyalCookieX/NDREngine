#include "ndrpch.h"
#include "core/Log.h"

#if NDR_PLATFORM_WINDOWS
#include <Windows.h>
#endif

namespace NDR
{
    void PrintToConsole(LogLevel level, const char* message)
    {
        const int32_t logColors[5] =
        {
            FOREGROUND_INTENSITY,                   // text grey
            FOREGROUND_GREEN,                       // text green
            FOREGROUND_RED | FOREGROUND_GREEN,      // text yellow
            FOREGROUND_RED,                         // text red
            BACKGROUND_RED                          // background red
        };
        
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(console, logColors[(int32_t)level]);
        OutputDebugStringA(message);
        size_t length = strlen(message);
        LPDWORD number_written = 0;
        WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), message, (DWORD)length, number_written, 0);
    }
}