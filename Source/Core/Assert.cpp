#include "ndrpch.h"
#include "Assert.h"

#include "Log.h"

namespace NDR
{
    void AssertMessage(bool expression, const char* message, const char* file, Int32 line)
    {
        if(!expression)
        {
            NDR_LOGFATAL("%s | %s @ LINE %d", message, file, line);
            DEBUGBREAK;
        }           
    }
}