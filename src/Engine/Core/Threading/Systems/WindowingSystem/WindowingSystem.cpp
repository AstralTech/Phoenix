#include "WindowingSystem.h"
#include "iostream"

namespace Engine {
    void WindowingSystem::HandleEvents() {
        while (true) {
            for (int i = 0; i < windows.size(); i++) {
                std::cout << "fdfsdfsd, " << i << std::endl;
                if (windows[i]->Opened)
                    windows[i]->platformWindow->ManageWindowEvents();
            }
        }
    }

    void WindowingSystem::OnStart() {
        windowManager = new PlatformWindowManager();

        EventThread = RequestThread(&WindowingSystem::HandleEvents, &(*this));
    }
    void WindowingSystem::OnEnd() {}

    void WindowingSystem::OpenWindowingWindow(WindowingWindow* window) {
        std::cout << "Opening Window: " << window->windowObject->name << "\n";

        PlatformWindow* platformWindow = new PlatformWindow(windowManager, window->windowObject->name, window->windowObject->size.x, window->windowObject->size.y);
        window->platformWindow = platformWindow;
        window->Opened = true;
    }

    void WindowingSystem::OpenWindowingWindows() {
        for (int i = 0; i < windows.size(); i++) {
            if (!windows[i]->Opened)
                OpenWindowingWindow(windows[i]);
        }

        for (int i = 0; i < windows.size(); i++) {
            windows[i]->platformWindow->UpdatePlatformWindow();
        }
    }

    void WindowingSystem::OnUpdate() {
        OpenWindowingWindows();
    }
}   