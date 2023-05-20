#include "WindowingSystem.h"
#include "iostream"

#include "../EventSystem/EventSystem.h"

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

    void WindowingSystem::ReadWindowEvents() {
        std::vector<Event*> events = windowManager->ReadEvents();
        for (int i = 0; i < events.size(); i++) {
            if (events[i]->GetType() == Event::Type::KeyPressed) {
                KeyPressedEvent* event = dynamic_cast<KeyPressedEvent*>(events[i]);

                eventSystem->ProcessEvent<KeyPressedEvent>(*event);
            } else {
                std::cout << "the window system does not support this window event";
            }
        }
        windowManager->ClearEvents();
    }

    void WindowingSystem::OnUpdate() {
        OpenWindowingWindows();
        ReadWindowEvents();
    }
}   