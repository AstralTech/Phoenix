#pragma once
#include "Gryphon.h"

namespace Phoenix {
    class PhoenixApplication : public Engine::Application {
    public:
        // Exection Manager
        Engine::ExecutionManager* executionManager;

        Engine::ExecutionGroup* renderingGroup;
        Engine::ExecutionGroup* eventGroup;

        Engine::RenderingSystem* renderingSystem;
        Engine::WindowingSystem* windowingSystem;
        Engine::EventSystem* eventSystem;

        // Application Types
        Engine::WindowObject* PhoenixWindow;
    public:
        PhoenixApplication() {}
    public:
        virtual void RunApp() override;
        virtual void UpdateApp() override;
        virtual void CloseApp() override;

        bool OnKeyPressed(Engine::KeyPressedEvent event);
    };
}