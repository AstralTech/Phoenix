#pragma once

#define X11 0
#define WAYLAND 1

#include "Windowing/LinuxPlatformWindow.h"
#include "../../Renderers/Renderer.h"

namespace Engine {
    class Platform {
    public:
        const char* GetName() { return "Linux"; }
    };
}