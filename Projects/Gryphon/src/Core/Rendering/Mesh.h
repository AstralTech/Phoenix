#pragma once

#include "vector"
#include "any"

#include "../../Renderers/RendererPlatformMesh.h"

namespace Engine {

    enum VertexPropertyType {
        Float2
    };
    
    class Vertex {
    public:
        std::vector<std::any> vert_values = {};
    };

    class Mesh {
    private:    
        std::vector<VertexPropertyType> vertex_props = {};
        std::vector<Vertex> verticies = {};
        bool IsBuilt = false;

        PlatformMesh platformMesh;
    public:
        bool HasMeshBeenBuilt() { return IsBuilt; }
        PlatformMesh GetPlatformMesh() { return platformMesh; }

        void SetPlatformMesh(PlatformMesh mesh) { platformMesh = mesh; }
        void SetAsBuilt() { IsBuilt = true; }
        void SetVertexProperties(std::vector<VertexPropertyType> props) { this->vertex_props = props; }
        void AddVertex(std::vector<std::any> vertex_properties) {
            Vertex new_vertex = Vertex();
            new_vertex.vert_values = vertex_properties;
            verticies.push_back(new_vertex);
        }
    };
}