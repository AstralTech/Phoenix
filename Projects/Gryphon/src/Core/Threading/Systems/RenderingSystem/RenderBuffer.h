#pragma once

#include "../../../Types/MultiData.h"

namespace Engine {
    struct RenderBuffer {
    public:
        Int2 RenderBufferSize;
    public:
        RenderBuffer(Int2 size) {
            this->RenderBufferSize = size;
        }
    };
}
