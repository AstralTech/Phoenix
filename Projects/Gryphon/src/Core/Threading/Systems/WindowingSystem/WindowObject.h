#pragma once
#include "../../../Types/MultiData.h"

#include "../RenderingSystem/RenderBuffer.h"

namespace Engine {
    class WindowObject {
    public:
        const char* name;
        Int2 size;

        std::vector<RenderBuffer*> render_buffers;
    public:
        WindowObject(const char* vName, Int2 vSize) {
            this->name = vName;
            this->size = vSize;
        }

        void AddRenderBuffer(RenderBuffer* render_buffer) {
            render_buffers.push_back(render_buffer);
        }
    };
}
