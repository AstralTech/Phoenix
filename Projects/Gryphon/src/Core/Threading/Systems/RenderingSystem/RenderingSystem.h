#pragma once
#include "../../ExecutionManager.h"

#include "../../../../Renderers/Renderer.h"

namespace Engine {
    class RenderingSystem : public ExecutionSystem {
    public:
        RendererLink* rendererLink;
    public:
        virtual void OnStart()override;
        virtual void OnUpdate() override;
        virtual void OnEnd() override;
    };
}