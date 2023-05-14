#pragma once

#include "WindowData.h"

namespace Engine {
    class WindowBase {
    protected:
        WindowData windowData;
    public:
        virtual void Open() = 0;
        virtual void Close() = 0;
        virtual void HandleEvents() = 0;
    };
}