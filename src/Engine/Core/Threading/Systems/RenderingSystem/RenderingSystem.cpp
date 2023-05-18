#include "RenderingSystem.h"
#include "iostream"

namespace Engine {
    void RenderingSystem::OnStart() {
        rendererLink = new RendererLink();
        rendererLink->Init();
    }
    void RenderingSystem::OnUpdate() {
 
    }
    void RenderingSystem::OnEnd() {

    }
}   