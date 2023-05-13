#pragma once

#define X11 0
#define WAYLAND 1

#include "../PlatformBase.h"

#if (LINUXOS_WINDOWING_SYSTEM == 0)
#include "Window/X11Window.h"
#elif (LINUXOS_WINDOWING_SYSTEM == 1)
#include "Window/WaylandWindow.h"
#endif

namespace Engine {
    class Platform : public Engine::PlatformBase {
    public:
        Platform() {}
    public:
        virtual const char* GetName() override { return "Linux"; }
        virtual ApplicationWindow* CreateWindow(WindowData data) override {
            return new PlatformWindow(data);
        }
    };
}