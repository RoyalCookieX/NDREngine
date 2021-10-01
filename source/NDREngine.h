#pragma once

#include <memory>
#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iostream>
#include <queue>

#include <glm/glm.hpp>
#include <glm/ext/quaternion_float.hpp>

#include "core/APICall.h"
#include "core/Engine.h"

#if (NDR_RELEASE && NDR_PLATFORM_WINDOWS)
#define NDRMain WinMain
#else
#define NDRMain main
#endif

