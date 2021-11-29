#include "ndrpch.h"
#include "Assert.h"

#include "Log.h"

#if _MSC_VER
    #define DEBUGBREAK __debugbreak()
#else
    #define DEBUGBREAK
#endif

namespace NDR
{
    void AssertMessage(bool expression, const char* message, const char* file, int32_t line)
    {
        if(!expression)
        {
            NDR_LOGFATAL("%s | %s @ LINE %d", message, file, line);
            DEBUGBREAK;
        }           
    }
}