#include "WindowingSystem.h"
#include "iostream"

namespace Engine {
    void WindowingSystem::OnStart() {
        windowManager = new PlatformWindowManager();
    }
    void WindowingSystem::OnEnd() {}

    void WindowingSystem::OpenWindowingWindow(WindowingWindow* window) {
        std::cout << "Opening Window: " << window->windowObject->name << "\n";

        PlatformWindow* platformWindow = new PlatformWindow(windowManager, window->windowObject->name, window->windowObject->size.x, window->windowObject->size.y);
        window->platformWindow = platformWindow;
        window->Opened = true;
        window->EventThread = RequestThread(&WindowingWindow::HandleEvents, &(*window));

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