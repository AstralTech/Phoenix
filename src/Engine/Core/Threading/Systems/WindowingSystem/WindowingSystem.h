#pragma once
#include "../../ExecutionManager.h"
#include "WindowObject.h"

#include "vector"

#include "../../../../Platforms/Platform.h"

namespace Engine {
    struct WindowingWindow {
    public:
        WindowObject* windowObject;
        PlatformWindow* platformWindow;
        bool Opened = false;

        ExecutionThread* EventThread;
    public:
        bool IsClosed() { return platformWindow->IsClosed(); }

        WindowingWindow(WindowObject* object) {
            this->windowObject = object;
        }

        void HandleEvents() {
            while (true) {
                if (Opened)
                    platformWindow->ManageWindowEvents();
            }
        }
    };

    class WindowingSystem : public ExecutionSystem {
    private:
        std::vector<WindowingWindow*> windows = {};
        WindowingWindow* mainWindow;


        PlatformWindowManager* windowManager;
    public:
        WindowingWindow* OpenAuxiliaryWindow(WindowObject* window) { 
            WindowingWindow* win = new WindowingWindow(window);
            windows.push_back(win);
            return win;
        }
        void OpenMainWindow(WindowObject* window) { 
            mainWindow = OpenAuxiliaryWindow(window);
        }

        void OpenWindowingWindow(WindowingWindow* window);
        void OpenWindowingWindows();

        bool WindowsClosed() { 
            if (mainWindow->platformWindow)
                return mainWindow->IsClosed();
            else 
                return false; 
        }

        virtual void OnStart()override;
        virtual void OnUpdate() override;
        virtual void OnEnd() override;
    };
}