#include "PhoenixApplication.h"
#include "iostream"

namespace Phoenix {
    void PhoenixApplication::RunApp() {
        std::cout << "Welcome to the Phoenix Text editor if your window does not open shortly then I have zero clue what is going on plese report this bug <3\n";

        // Create the rendering group
        renderingGroup = new Engine::ExecutionGroup(); 

        windowingSystem = new Engine::WindowingSystem();
        PhoenixWindow = new Engine::WindowObject("Phoenix Text Editor [v0.05][x86][Linux]", Int2(1920, 1080));
        windowingSystem->OpenMainWindow(PhoenixWindow);

        renderingSystem = new Engine::RenderingSystem();

        BackgroundRenderingBuffer = new Engine::RenderBuffer(Int2(1920, 1080));
        TestWindowRenderingBuffer = new Engine::RenderBuffer(Int2(200, 300));

        renderingSystem->RegisterBuffer(BackgroundRenderingBuffer);
        renderingSystem->RegisterBuffer(TestWindowRenderingBuffer);

        renderingGroup->BindSystem(windowingSystem);
        renderingGroup->BindSystem(renderingSystem);


        // Create the event group
        eventGroup = new Engine::ExecutionGroup();
        eventSystem = new Engine::EventSystem();

        eventGroup->BindSystem(eventSystem);

        windowingSystem->SetEventManager(eventSystem);

        // Create the execution manager
        executionManager = new Engine::ExecutionManager();
        executionManager->BindGroup(renderingGroup);
        executionManager->BindGroup(eventGroup);

        executionManager->StartExecution();
    }

    void PhoenixApplication::UpdateApp() {
        if (windowingSystem->WindowsClosed())
            EndApp();

        #if 1 == 0
        renderingSystem->BindBuffer(BackgroundRenderingBuffer);
        renderingSystem->Clear(Color(128, 128, 128, 1));
        
        windowingSystem->DrawToWindow_Background(PhoenixWindow);

        renderingSystem->BindBuffer(TestWindowRenderingBuffer);
        renderingSystem->Clear(Color(255, 0, 0, 1));
        
        windowingSystem->DrawToWindow_Object(PhoenixWindow, Int2(100, 100));
        #endif
    }

    void PhoenixApplication::CloseApp() {
        executionManager->StopExecution();
    }
}