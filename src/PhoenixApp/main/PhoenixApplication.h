#pragma once
#include "Engine/Engine.h"

namespace Phoenix {
    class PhoenixApplication : public Engine::Application {
    public:
        Engine::ApplicationWindow* main_window;

        // Exection Manager
        Engine::ExecutionManager* executionManager;

        Engine::ExecutionGroup* renderingGroup;
        Engine::ExecutionGroup* eventGroup;

        Engine::RenderingSystem* renderingSystem;
        Engine::EventSystem* eventSystem;
    public:
        PhoenixApplication() {}
    public:
        virtual void RunApp() override;
        virtual void UpdateApp() override;
        virtual void CloseApp() override;
    };
}