#include "ndrpch.h"
#include "Core/Log.h"

#include <Windows.h>

namespace NDR
{
    void Log::LogConsole(const char* message, Int32 color)
    {
        const HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(consoleHandle, color);
        OutputDebugStringA(message);
        const USize length = strlen(message);
        const LPDWORD number_written = nullptr;
        WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), message, (DWORD)length, number_written, nullptr);
    }

    Int32 Log::LogLevelToConsoleColor(LogLevel level)
    {
        static Int32 levels[5] = { 1, 2, 6, 4, 64 };
        return levels[(Int32)level];
    }


}