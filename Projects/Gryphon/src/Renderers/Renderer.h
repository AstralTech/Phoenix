#pragma once

#include "Settings.h"

#define OPENGL 0
#define VULKAN 1
#define DIRECTX 2
#define METAL 3

#if (GRYPHON_RENDERER == OPENGL)
#include "OpenGL/OpenGL.h"
#elif (GRYPHON_RENDERER == VULKAN) 
#include "Vulkan/Vulkan.h"
#elif (GRYPHON_RENDERER == DIRECTX)
#include "DirectX/DirectX.h"
#elif (GRYPHON_RENDERER == METAL)
#include "Metal/Metal.h"
#endif