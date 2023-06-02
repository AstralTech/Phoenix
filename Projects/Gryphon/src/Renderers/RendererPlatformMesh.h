#pragma once

#include "Settings.h"

#if (GRYPHON_RENDERER == OPENGL)
#include "OpenGL/OpenGLMesh.h"
#elif (GRYPHON_RENDERER == VULKAN) 
#include "Vulkan/VulkanMesh.h"
#elif (GRYPHON_RENDERER == DIRECTX)
#include "DirectX/DirectXMesh.h"
#elif (GRYPHON_RENDERER == METAL)
#include "Metal/MetalMesh.h"
#endif