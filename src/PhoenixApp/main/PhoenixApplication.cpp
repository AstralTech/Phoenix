#include "PhoenixApplication.h"
#include "iostream"

namespace Phoenix {
    void PhoenixApplication::RunApp() {
        std::cout << "Welcome to the Phoenix Text editor if your window does not open shortly then I have zero clue what is going on plese report this bug <3";

        // Create the rendering group
        renderingGroup = new Engine::ExecutionGroup(); 
        renderingSystem = new Engine::RenderingSystem();

        renderingGroup->BindSystem(renderingSystem);

        // Create the event group
        eventGroup = new Engine::ExecutionGroup();
        eventSystem = new Engine::EventSystem();

        eventGroup->BindSystem(eventSystem);

        // Create the execution manager
        executionManager = new Engine::ExecutionManager();
        executionManager->BindGroup(renderingGroup);
        executionManager->BindGroup(eventGroup);

        executionManager->StartExecution();

        main_window = platform->CreateWindow(Engine::WindowData(
            "Phoenix Text Editor v0.01, x86", // Window Name
            Int2(1280, 720) // Window Size
        ), eventSystem);

        main_window->Open();
    }

    void PhoenixApplication::UpdateApp() {

    }

    void PhoenixApplication::CloseApp() {
        executionManager->StopExecution();
        main_window->Close();
    }
}