#pragma once 

#include "../Types/MultiData.h"

namespace Engine {
    struct WindowData {
        const char* WindowName;
        Int2 WindowSize;
    public:
        WindowData() {};
        WindowData(const char* windowName, Int2 windowSize) {
            this->WindowName = windowName;
            this->WindowSize = windowSize;
        }
    };
}
