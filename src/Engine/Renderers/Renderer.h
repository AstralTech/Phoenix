#pragma once

#include "../../Settings.h"

#define OPENGL 0
#define VULKAN 1
#define DIRECTX 2
#define METAL 3

#if (ENGINE_RENDERER == OPENGL)
#include "OpenGL/OpenGL.h"
#elif (ENGINE_RENDERER == VULKAN) 
#include "Vulkan/Vulkan.h"
#elif (ENGINE_RENDERER == DIRECTX)
#include "DirectX/DirectX.h"
#elif (ENGINE_RENDERER == METAL)
#include "Metal/Metal.h"
#endif