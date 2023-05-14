#pragma once
#include "iostream"

#include "../../../Core/Window/Window.h"

namespace Engine {
    class PlatformWindow : public Window {
    public:
        PlatformWindow(WindowData data, EventSystem* event) { 
            std::cout << "\nWHY ARE YOU USING THIS SHIT YOU KNOW THAT I AM A LAZY AF DEVELOPER SO THIS SHIT AINT GOING TO WORK BUDDY PLEASE USE X11 I AM LAZY\n";
            this->windowData = data;
        }
    };
}