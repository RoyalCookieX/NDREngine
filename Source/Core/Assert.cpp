#include "ndrpch.h"
#include "Assert.h"

namespace NDR
{
    void Assert::AssertMessage(bool expression, const char* message, const char* file, Int32 line)
    {
        if(!expression)
        {
            NDR_LOGFATAL("%s | %s @ LINE %d", message, file, line);
            DEBUGBREAK;
        }
    }

}