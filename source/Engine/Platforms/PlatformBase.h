#pragma once

#include "../Core/Window/Window.h"


namespace Engine {
    class ApplicationWindow : public WindowBase {
    public:
        virtual void Open() = 0;
        virtual void Update() = 0;
        virtual void Close() = 0;
    };

    class PlatformBase {
    public:
        virtual const char* GetName() = 0;

        virtual ApplicationWindow* CreateWindow(WindowData data) = 0;
    };
}