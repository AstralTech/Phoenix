#pragma once

#include "WindowData.h"

namespace Engine {
    class WindowBase {
    protected:
        WindowData windowData;

        bool is_open = true;
    public:
        virtual void Open() = 0;
        virtual void Close() = 0;
        virtual void Render() = 0;
        virtual void HandleEvents() = 0;

        bool IsOpen() { return is_open; }
    };
}