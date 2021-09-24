#pragma once
#include "core/Engine.h"

#if (NDR_RELEASE && NDR_PLATFORM_WINDOWS)
#define NDRMain WinMain
#else
#define NDRMain main
#endif

