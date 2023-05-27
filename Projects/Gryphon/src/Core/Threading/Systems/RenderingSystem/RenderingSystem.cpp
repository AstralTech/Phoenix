#include "RenderingSystem.h"
#include "iostream"

namespace Engine {
    void RenderingSystem::RegisterBuffer(RenderBuffer* renderBuffer) {
        RenderingRenderBuffer* newRenderingBuffer = new RenderingRenderBuffer(renderBuffer); 
        renderBuffers.push_back(newRenderingBuffer);
    }

    void RenderingSystem::OnStart() {
        rendererLink = new RendererLink();
        rendererLink->Init();
    }
    void RenderingSystem::OnUpdate() {
        for (int i = 0; i < renderBuffers.size(); i++) {

        }
    }
    void RenderingSystem::OnEnd() {

    }
}   