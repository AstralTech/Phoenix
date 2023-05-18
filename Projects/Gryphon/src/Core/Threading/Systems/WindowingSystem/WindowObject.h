#pragma once
#include "../../../Types/MultiData.h"

namespace Engine {
    class WindowObject {
    public:
        const char* name;
        Int2 size;
    public:
        WindowObject(const char* vName, Int2 vSize) {
            this->name = vName;
            this->size = vSize;
        }
    };
}
