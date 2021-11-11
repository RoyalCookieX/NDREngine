#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "core/Engine.h"
#include "core/Window.h"
#include "core/Log.h"
#include "graphics/Renderer.h"
#include "runtime/objects/Camera.h"
#include "utility/AssetManager.h"
#include "utility/Memory.h"
#include "utility/Time.h"

#if (NDR_RELEASE && NDR_PLATFORM_WINDOWS)
#define NDRMain WinMain
#else
#define NDRMain main
#endif