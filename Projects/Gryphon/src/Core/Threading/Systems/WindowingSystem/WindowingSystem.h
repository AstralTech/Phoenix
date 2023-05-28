#pragma once
#include "../../ExecutionManager.h"
#include "WindowObject.h"

#include "vector"

#include "../../../../Platforms/Platform.h"

namespace Engine {
    class EventSystem;
    class RenderingSystem;

    struct RenderBuffer;
    
    enum RenderBufferType {
        Background, Object
    };

    struct WindowingWindow {
    public:
        WindowObject* windowObject;
        PlatformWindow* platformWindow;
        bool Opened = false;
    public:
        bool IsClosed() { return platformWindow->IsClosed(); }

        WindowingWindow(WindowObject* object) {
            this->windowObject = object;
        }
    };

    class WindowingSystem : public ExecutionSystem {
    private:
        std::vector<WindowingWindow*> windows = {};
        WindowingWindow* mainWindow;

        //ExecutionThread* eventThread;

        RenderingSystem* renderingSystem;

        PlatformWindowManager* windowManager;
        EventSystem* eventSystem;
    public:
        WindowingWindow* OpenAuxiliaryWindow(WindowObject* window) { 
            WindowingWindow* win = new WindowingWindow(window);
            windows.push_back(win);
            return win;
        }
        void OpenMainWindow(WindowObject* window) { 
            mainWindow = OpenAuxiliaryWindow(window);
        }

        void SetEventManager(EventSystem* EventSystem) { eventSystem = EventSystem; }

        void OpenWindowingWindow(WindowingWindow* window);
        void OpenWindowingWindows();

        void ReadWindowEvents();

        bool WindowsClosed() { 
            if (mainWindow->platformWindow)
                return mainWindow->IsClosed();
            else 
                return false; 
        }

        void DrawToWindow(WindowObject* window_to_draw, RenderBuffer* render_buffer, RenderBufferType render_buffer_type, Int2 position = Int2(0));

        virtual void OnStart()override;
        virtual void OnUpdate() override;
        virtual void OnEnd() override;
    };
}