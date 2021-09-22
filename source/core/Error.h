#pragma once
#include <cstdio>
#include <glad/glad.h>

#if (NDR_DEBUG || NDR_FORCE_LOG)
#define GLCall(x) NDR::ClearGLErrors();\
    x;\
    NDR::PrintGLErrors(__FILE__, __LINE__)
#else
#define GLCall(x) x
#endif

namespace NDR
{
    static void ClearGLErrors()
    {
        while(glGetError() != GL_NO_ERROR) { }
    }

    static void PrintGLErrors(const char* file, int line)
    {
        while(GLenum error = glGetError())
        {
            printf("%s @ LINE %d -> [OpenGL Error]: 0x%x (%d)\n", file, line, error, error);
        }
    }
}