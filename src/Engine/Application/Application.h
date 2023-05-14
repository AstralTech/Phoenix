#pragma once
#include "../Platforms/Platform.h"

namespace Engine {
    class Application {
    protected:
        bool IsClosed = false;
        void EndApp() { IsClosed = true; }
    public:
        Engine::Platform* platform;
    public:
        void Init() {
            platform = new Engine::Platform();
        }
    public:
        Application() {}

        virtual void RunApp() = 0;
        virtual void UpdateApp() = 0;
        virtual void CloseApp() = 0;
        
        bool IsRunning() { return !IsClosed; };
    };
}