#pragma once
#include "../PlatformBase.h"

namespace Engine {
    class Platform : public Engine::PlatformBase {
    public:
        Platform() {}
    public:
        virtual const char* GetName() override { return "MacOS"; }
    };
}