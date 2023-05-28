#include "WindowingSystem.h"
#include "iostream"

#include "../EventSystem/EventSystem.h"
#include "../RenderingSystem/RenderingSystem.h"

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
        //window->EventThread = RequestThread(&WindowingWindow::HandleEvents, &(*window));

    }

    void WindowingSystem::OpenWindowingWindows() {
        //eventThread = RequestThread(&WindowingSystem::ReadWindowEvents, &(*this));

        for (int i = 0; i < windows.size(); i++) {
            if (!windows[i]->Opened)
                OpenWindowingWindow(windows[i]);
        }

        for (int i = 0; i < windows.size(); i++) {
            windows[i]->platformWindow->UpdatePlatformWindow();

            windows[i]->platformWindow->StartWindowDraw();

            for (int k = 0; k < windows[i]->windowObject->render_buffers.size(); k++) {
                renderingSystem->DrawRenderBuffer(windows[i]->windowObject->render_buffers[k]);
            }

            windows[i]->platformWindow->EndWindowDraw();
        }
    }

    void WindowingSystem::ReadWindowEvents() {
        //while (true) {
            windowManager->UpdateEventQueue();


            std::vector<Event*> events = windowManager->ReadEvents();
            for (int i = 0; i < events.size(); i++) {
                if (events[i]->GetType() == Event::Type::KeyPressed) {
                    KeyPressedEvent* event = dynamic_cast<KeyPressedEvent*>(events[i]);

                    eventSystem->ProcessEvent<KeyPressedEvent>(*event);
                } else if (events[i]->GetType() == Event::Type::KeyReleased) {
                    KeyReleasedEvent* event = dynamic_cast<KeyReleasedEvent*>(events[i]);

                    eventSystem->ProcessEvent<KeyReleasedEvent>(*event);
                } else {
                    std::cout << "the window system does not support this window event";
                }
            }
            windowManager->ClearEvents();
        //}
    }

    void WindowingSystem::OnUpdate() {
        if (!renderingSystem)
            renderingSystem = GetExecutionSystem<RenderingSystem>();

        OpenWindowingWindows();
        ReadWindowEvents();
    }

    void WindowingSystem::DrawToWindow(WindowObject* window_to_draw, RenderBuffer* render_buffer, RenderBufferType render_buffer_type, Int2 position) {
        WindowingWindow* window = 0;
        for (int i = 0; i < windows.size(); i++) {
            if (windows[i]->windowObject == window_to_draw) {
                window = windows[i];
                break;
            }
        }

        window->platformWindow->StartWindowDraw();

        window->platformWindow->EndWindowDraw();
    }
}   