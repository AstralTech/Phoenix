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
        WindowsRenderingBuffer = new Engine::RenderBuffer(Int2(1920, 1080));

        PhoenixWindow->AddRenderBuffer(BackgroundRenderingBuffer);
        PhoenixWindow->AddRenderBuffer(WindowsRenderingBuffer);

        renderingSystem->RegisterBuffer(BackgroundRenderingBuffer);
        renderingSystem->RegisterBuffer(WindowsRenderingBuffer);

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

        // build the meshes
        SquareMesh = new Engine::Mesh();
        SquareMesh->SetVertexProperties({ Engine::VertexPropertyType::Float2, Engine::VertexPropertyType::Color });


        SquareMesh->AddVertex({ Float2(-0.5f,  0.5f), Color(255,   0,   0, 1.0) });
        SquareMesh->AddVertex({ Float2(-0.5f, -0.5f), Color(  0, 255,   0, 1.0) });
        SquareMesh->AddVertex({ Float2( 0.5f, -0.5f), Color(  0,   0, 255, 1.0) });
        SquareMesh->AddVertex({ Float2( 0.5f,  0.5f), Color(255, 255, 255, 1.0) });

        SquareMesh->AddTriangle(Int3(0, 1, 2));
        SquareMesh->AddTriangle(Int3(0, 3, 2));

        renderingSystem->BuildMesh(SquareMesh);
    }

    void PhoenixApplication::UpdateApp() {
        if (windowingSystem->WindowsClosed())
            EndApp();

        renderingSystem->BeginRendererFrame();

        renderingSystem->BindRenderBuffer(BackgroundRenderingBuffer);
        renderingSystem->Clear(Color(70, 70, 70, 1));
        renderingSystem->DrawMesh(SquareMesh);

        renderingSystem->BindRenderBuffer(WindowsRenderingBuffer);
        renderingSystem->Clear(Color(0, 0, 0, 0));

        renderingSystem->EndRendererFrame();
    }

    void PhoenixApplication::CloseApp() {
        executionManager->StopExecution();
    }
}