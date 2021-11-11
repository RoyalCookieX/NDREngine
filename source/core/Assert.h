#pragma once

#define NDR_ASSERT(expression, message) NDR::AssertMessage(expression, message, __FILE__, __LINE__)

namespace NDR
{
    extern void AssertMessage(bool expression, const char* format, const char* file, int32_t line);
}