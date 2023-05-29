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
        
        RenderingRenderBuffer* myRenderingBuffer = GetRenderingRenderBuffer(renderBuffer);
        rendererLink->DrawRenderBuffer(myRenderingBuffer->platformRenderBuffer);
    }

    void RenderingSystem::OnStart() {

    }
    void RenderingSystem::OnUpdate() {
        if (!rendererLink) {
            rendererLink = new RendererLink();
            rendererLink->Init();
        }

        for (int i = 0; i < renderBuffers.size(); i++) {
            if (!renderBuffers[i]->platformRenderBuffer) {
                renderBuffers[i]->platformRenderBuffer = new PlatformRenderBuffer(renderBuffers[i]->renderBuffer);
            }
        }

        working_on_render = true;

        for (int k = 0; k < toRenderFrame.commands.size(); k++) {
            if (toRenderFrame.commands[k].name == "bind_render_buffer") {
                Internal_BindRenderBuffer(std::any_cast<RenderBuffer*>(toRenderFrame.commands[k].args[0]));
            }
            if (toRenderFrame.commands[k].name == "clear_buffer") {
                Internal_Clear(std::any_cast<Color>(toRenderFrame.commands[k].args[0]));
            }
        }

        working_on_render = false;
    }
    void RenderingSystem::OnEnd() {

    }

    void RenderingSystem::Internal_BindRenderBuffer(RenderBuffer* renderBuffer) {
        RenderingRenderBuffer* myRenderingBuffer = GetRenderingRenderBuffer(renderBuffer);
        rendererLink->BindRenderBuffer(myRenderingBuffer->platformRenderBuffer);
    }
    void RenderingSystem::Internal_Clear(Color color) {
        rendererLink->ClearScreen(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a);
    }
}   