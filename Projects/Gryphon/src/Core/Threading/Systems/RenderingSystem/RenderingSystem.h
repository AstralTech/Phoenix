#pragma once
#include "vector"

#include "../../ExecutionManager.h"
#include "../../../../Renderers/Renderer.h"
#include "RenderBuffer.h"

namespace Engine {
    struct RenderingRenderBuffer {
    public:
        RenderBuffer* renderBuffer;
        //PlatformRenderBuffer* platformRenderBuffer;

        bool initilized = false;
    public:
        RenderingRenderBuffer(RenderBuffer* object) {
            this->renderBuffer = object;
        }
    };

    class RenderingSystem : public ExecutionSystem {
    public:
        RendererLink* rendererLink;

        std::vector<RenderingRenderBuffer*> renderBuffers = {};
    public:
        void RegisterBuffer(RenderBuffer* renderBuffer);

        virtual void OnStart()override;
        virtual void OnUpdate() override;
        virtual void OnEnd() override;
    };
}