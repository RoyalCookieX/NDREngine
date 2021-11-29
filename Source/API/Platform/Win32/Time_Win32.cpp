#include "ndrpch.h"
#include "utility/Time.h"

namespace NDR
{
    static float lastTime = 0;

    float Time::GetTime()
    {
        return (float)glfwGetTime();
    }
    
    float Time::GetDeltaTime()
    {
        const float currentTime = (float)glfwGetTime();
        const float deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        return deltaTime;
    }
}