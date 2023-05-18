#pragma once
#include "../../ExecutionManager.h"
#include "vector"

#include "Key.h"

// I know i wrote that i did crap on this but lets be honest i did not

namespace Engine {
    class PlatformWindow;

    class EventSystem : public ExecutionSystem {
    private:
        std::vector<Key> keysDown;
    public:
        virtual void OnStart()override;
        virtual void OnUpdate() override;
        virtual void OnEnd() override;
    };
}