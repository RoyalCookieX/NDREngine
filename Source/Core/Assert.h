#pragma once
#include "Log.h"

#define NDR_ASSERT(expression, message) NDR::Assert::AssertMessage(expression, message, __FILE__, __LINE__)

namespace NDR
{
    class Assert
    {
    public:
        static void AssertMessage(bool expression, const char* message, const char* file, Int32 line);
    };
}