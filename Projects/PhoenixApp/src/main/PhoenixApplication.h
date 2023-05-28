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

        // Rendering Types
        Engine::RenderBuffer* BackgroundRenderingBuffer; // This buffer is for rendering the background like docking indicators
        Engine::RenderBuffer* WindowsRenderingBuffer; // This is the actuall windows that you can drag around

        // Application Types
        Engine::WindowObject* PhoenixWindow;
    public:
        PhoenixApplication() {}
    public:
        virtual void RunApp() override;
        virtual void UpdateApp() override;
        virtual void CloseApp() override;
    };
}