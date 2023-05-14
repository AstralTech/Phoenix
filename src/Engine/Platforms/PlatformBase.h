#pragma once

#include "../Core/Window/Window.h"
#include "../Core/Threading/Systems/EventSystem/EventSystem.h"

namespace Engine {
    class ApplicationWindow : public WindowBase {
    public:
        virtual void Open() = 0;
        virtual void Close() = 0;

        virtual void HandleEvents() = 0;
    };

    class PlatformBase {
    public:
        virtual const char* GetName() = 0;

        virtual ApplicationWindow* CreateWindow(WindowData data, EventSystem* event) = 0;
    };
}