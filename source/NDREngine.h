#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "core/Engine.h"
#include "core/Window.h"
#include "graphics/Renderer.h"
#include "runtime/objects/Camera.h"
#include "utility/AssetManager.h"

#if (NDR_RELEASE && NDR_PLATFORM_WINDOWS)
#define NDRMain WinMain
#else
#define NDRMain main
#endif