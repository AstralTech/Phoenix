#include "RenderingSystem.h"
#include "iostream"

namespace Engine {
    void RenderingSystem::RegisterBuffer(RenderBuffer* renderBuffer) {
        RenderingRenderBuffer* newRenderingBuffer = new RenderingRenderBuffer(renderBuffer); 
        renderBuffers.push_back(newRenderingBuffer);
    }   

    void RenderingSystem::DrawRenderBuffer(RenderBuffer* renderBuffer) {
        if (!rendererLink)
            return;
        rendererLink->DrawRenderBuffer(renderBuffer);
    }

    void RenderingSystem::OnStart() {

    }
    void RenderingSystem::OnUpdate() {
        if (!rendererLink) {
            rendererLink = new RendererLink();
            rendererLink->Init();
        }
    }
    void RenderingSystem::OnEnd() {

    }
}   