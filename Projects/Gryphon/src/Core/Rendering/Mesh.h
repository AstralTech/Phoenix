#pragma once

#include "vector"
#include "any"

#include "../../Renderers/RendererPlatformMesh.h"
#include "../Types/MultiData.h"

namespace Engine {

    enum class VertexPropertyType {
        Float2, Flaot3, Float4,
        Color
    };
    
    class Vertex {
    public:
        std::vector<std::any> vert_values = {};
    };

    class Mesh {
    private:    
        std::vector<VertexPropertyType> vertex_props = {};
        std::vector<Vertex> vertices = {};
        bool IsBuilt = false;

        std::vector<Int3> triangles = {};

        PlatformMesh platformMesh;
    public:
        bool HasMeshBeenBuilt() { return IsBuilt; }
        PlatformMesh GetPlatformMesh() { return platformMesh; }
        std::vector<VertexPropertyType> GetVertexProperties() { return vertex_props; }
        std::vector<Vertex> GetVertices() { return vertices; }
        std::vector<Int3> GetTriangles() { return triangles; }
        

        void SetPlatformMesh(PlatformMesh mesh) { platformMesh = mesh; }
        void SetAsBuilt() { IsBuilt = true; }
        void SetVertexProperties(std::vector<VertexPropertyType> props) { this->vertex_props = props; }
        
        void AddTriangle(Int3 tri) { triangles.push_back(tri); }
        void AddVertex(std::vector<std::any> vertex_properties) {
            Vertex new_vertex = Vertex();
            new_vertex.vert_values = vertex_properties;
            vertices.push_back(new_vertex);
        }
    };
}