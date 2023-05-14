#pragma once
#include "../../ExecutionManager.h"
#include "vector"

namespace Engine {
    class PlatformWindow;

    class EventSystem : public ExecutionSystem {
    private:
        std::vector<PlatformWindow*> windows_open = {};
    public:
        virtual void OnStart()override;
        virtual void OnUpdate() override;
        virtual void OnEnd() override;

        void RegisterWindow(PlatformWindow* win);
    };
}