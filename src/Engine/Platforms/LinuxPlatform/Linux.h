#pragma once

#define X11 0
#define WAYLAND 1

#include "Windowing/LinuxPlatformWindow.h"

namespace Engine {
    class Platform {
    public:
        const char* GetName() { return "Linux"; }
    };
}