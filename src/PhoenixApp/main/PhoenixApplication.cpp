#include "PhoenixApplication.h"
#include "iostream"

namespace Phoenix {
    void PhoenixApplication::RunApp() {
        std::cout << "Welcome to the Phoenix Text editor if your window does not open shortly then I have zero clue what is going on plese report this bug <3\n";

        // Create the rendering group
        renderingGroup = new Engine::ExecutionGroup(); 

        windowingSystem = new Engine::WindowingSystem();
        Engine::WindowObject* PhoenixWindow = new Engine::WindowObject("Phoenix Text Editor [v0.01][x86][Linux]", Int2(1920, 1080));
        Engine::WindowObject* testWindow = new Engine::WindowObject("This is an amazing test window", Int2(1280, 720));
        windowingSystem->OpenMainWindow(PhoenixWindow);
        windowingSystem->OpenAuxiliaryWindow(testWindow);

        renderingSystem = new Engine::RenderingSystem();

        renderingGroup->BindSystem(windowingSystem);
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
    }

    void PhoenixApplication::UpdateApp() {
        if (windowingSystem->WindowsClosed())
            EndApp();
    }

    void PhoenixApplication::CloseApp() {
        executionManager->StopExecution();
    }
}