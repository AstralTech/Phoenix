#pragma once
#include "../../ExecutionManager.h"

namespace Engine {
    class RenderingSystem : public ExecutionSystem {
    public:
        virtual void OnStart()override;
        virtual void OnUpdate() override;
        virtual void OnEnd() override;
    };
}