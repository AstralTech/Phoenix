#pragma once

#include "vector"

namespace Engine {
    class PlatformMesh {
    public:
        unsigned int MeshVAO;
        std::vector<unsigned int> MeshVBOs = {};
        unsigned int MeshIBO;
        int TriangleSize;
    };
}
