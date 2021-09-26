#pragma once

#if (NDR_DEBUG || NDR_FORCE_LOG)
    #ifdef NDR_GRAPHICSAPI_OPENGL
        #define GRAPHICSAPICALL(x) NDR::ClearGLErrors();\
        x;\
        NDR::PrintGLErrors(__FILE__, #x, __LINE__)
    #else
        #define GRAPHICSAPICALL(x) x
    #endif
#endif

namespace NDR
{
#ifdef NDR_GRAPHICSAPI_OPENGL
    static void ClearGLErrors()
    {
        while(glGetError() != GL_NO_ERROR) { }
    }

    static void PrintGLErrors(const char* file, const char* glCall, int line)
    {
        while(const GLenum error = glGetError())
        {
            char* errorMsg;
            switch (error)
            {
                case 0x500: errorMsg = "GL INVALID ENUM"; break;
                case 0x501: errorMsg = "GL INVALID VALUE"; break;
                case 0x502: errorMsg = "GL INVALID OPERATION"; break;
                case 0x503: errorMsg = "GL STACK OVERFLOW"; break;
                case 0x504: errorMsg = "GL STACK UNDERFLOW"; break;
                case 0x505: errorMsg = "GL OUT OF MEMORY"; break;
                case 0x506: errorMsg = "GL INVALID FRAMEBUFFER OPERATION"; break;
                default: errorMsg = "GL UNKNOWN"; break;
            }
            printf("%s @ LINE %d -> [OpenGL Error (%s)]: %s\n", file, line, errorMsg, glCall);
        }
    }
#endif
}