#pragma once

#include "GL/glew.h"

#include "../../Platforms/Platform.h"
#include "iostream"

#include "../../Core/Threading/Systems/RenderingSystem/RenderBuffer.h"
#include "OpenGLRenderBuffer.h"
#include "OpenGLMeshBuilder.h"
#include "OpenGLMesh.h"

#include "../../Core/Types/MultiData.h"

namespace Engine {
    static unsigned int CompileShader(unsigned int type, const std::string& source) {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)alloca(sizeof(char) * length);
            glGetShaderInfoLog(id, length, &length, message);
            std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment ") << "shader\n";
            std::cout << message << "\n";
        }

        return id;
    }
    static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
        unsigned int program = glCreateProgram();
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
   } 

    class RendererLink {
    public:
        unsigned int FrameBufferVAO;
        unsigned int FrameBufferVerticies;
        unsigned int FrameBufferShader;

        unsigned int basic_shader;

        unsigned int current_frame_buffer = 0;
    public:
        void Init() {
            float vertex[24] = {
                -1.0,  1.0, 0.0, 0.0,
                -1.0, -1.0, 0.0, 1.0,
                 1.0, -1.0, 1.0, 1.0,

                -1.0,  1.0, 0.0, 0.0,
                 1.0,  1.0, 1.0, 0.0,
                 1.0, -1.0, 1.0, 1.0
            };
            
            glGenVertexArrays(1, &FrameBufferVAO);
            glBindVertexArray(FrameBufferVAO);

            glGenBuffers(1, &FrameBufferVerticies);
            glBindBuffer(GL_ARRAY_BUFFER, FrameBufferVerticies);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, vertex, GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);

            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (const void*)(sizeof(float) * 2));

            std::string vertexShader = R"(
                #version 330 core

                layout(location = 0) in vec2 position;
                layout(location = 1) in vec2 texCoord;

                out vec2 vTexCoord;

                void main() {
                    vTexCoord = vec2(texCoord.x, -texCoord.y);

                    gl_Position = vec4(position, 0.0, 1.0);
                }
            )";

            std::string fragmentShader = R"(
                #version 330 core

                layout(location = 0) out vec4 color;

                in vec2 vTexCoord;
                uniform sampler2D screenTexture;

                void main() {
                    color = texture(screenTexture, vTexCoord);
                }           
            )";

            FrameBufferShader = CreateShader(vertexShader, fragmentShader);

            std::string vertexShader2 = R"(
                #version 330 core

                layout(location = 0) in vec2 position;
                layout(location = 1) in vec4 color;

                out vec4 vColor;

                void main() {
                    vColor = color;
                    gl_Position = vec4(position, 0.0, 1.0);
                }
            )";

            std::string fragmentShader2 = R"(
                #version 330 core

                layout(location = 0) out vec4 color;

                in vec4 vColor;

                void main() {
                    color = vColor;
                }           
            )";

            basic_shader = CreateShader(vertexShader2, fragmentShader2);
        }

        void BindRenderBuffer(PlatformRenderBuffer* buffer) {
            buffer->Bind();
            current_frame_buffer = buffer->framebuffer;
        }

        void DrawRenderBuffer(PlatformRenderBuffer* buffer) {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            buffer->BindForRendering();

            glDisable(GL_DEPTH_TEST);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glBindVertexArray(FrameBufferVAO);
            glUseProgram(FrameBufferShader);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            glEnable(GL_DEPTH_TEST);
        }

        // Renderer Rendering Routines
        void ClearScreen(float r, float g, float b, float a) {
            glBindFramebuffer(GL_FRAMEBUFFER, current_frame_buffer);

            glClearColor(r, g, b, a);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void DrawMesh(PlatformMesh mesh) {
            glBindFramebuffer(GL_FRAMEBUFFER, current_frame_buffer);

            glBindVertexArray(mesh.MeshVAO);
            glUseProgram(basic_shader);
            glDrawElements(GL_TRIANGLES, mesh.TriangleSize * 3, GL_UNSIGNED_INT, nullptr);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void BuildPlatformMesh(Mesh* mesh) {
            PlatformMesh new_mesh = PlatformMesh();
            
            glGenVertexArrays(1, &new_mesh.MeshVAO);
            glBindVertexArray(new_mesh.MeshVAO);

            std::vector<VertexPropertyType> vertex_properties = mesh->GetVertexProperties();
            std::vector<Vertex> vertices = mesh->GetVertices();

            unsigned int* mesh_vbos = new unsigned int[mesh->GetVertexProperties().size()];

            glGenBuffers(mesh->GetVertexProperties().size(), mesh_vbos);

            for (int i = 0; i < mesh->GetVertexProperties().size(); i++) {
                new_mesh.MeshVBOs.push_back(mesh_vbos[i]);
            }

            for (int i = 0; i < vertex_properties.size(); i++) {
                std::cout << new_mesh.MeshVBOs[i] << "\n";
                glBindBuffer(GL_ARRAY_BUFFER, new_mesh.MeshVBOs[i]);

                if (vertex_properties[i] == VertexPropertyType::Float2) {
                    std::vector<float> vert = {};
                    for (int k = 0; k < vertices.size(); k++) {
                        Float2 vertexvalue = std::any_cast<Float2>(vertices[k].vert_values[i]);
                        vert.push_back(vertexvalue.x);
                        vert.push_back(vertexvalue.y);
                    }

                    glBufferData(GL_ARRAY_BUFFER, sizeof(vert[0]) * vert.size(), &vert[0], GL_STATIC_DRAW);

                    glEnableVertexAttribArray(i);
                    glVertexAttribPointer(i, 2, GL_FLOAT, GL_FALSE, 0, 0);
                } else if (vertex_properties[i] == VertexPropertyType::Color) {

                    std::vector<float> vert = {};
                    for (int k = 0; k < vertices.size(); k++) {
                        Color vertexvalue = std::any_cast<Color>(vertices[k].vert_values[i]);
                        vert.push_back(vertexvalue.r / 255.0f);
                        vert.push_back(vertexvalue.g / 255.0f);
                        vert.push_back(vertexvalue.b / 255.0f);
                        vert.push_back(vertexvalue.a);
                    }

                    glBufferData(GL_ARRAY_BUFFER, sizeof(vert[0]) * vert.size(), &vert[0], GL_STATIC_DRAW);

                    glEnableVertexAttribArray(i);
                    glVertexAttribPointer(i, 4, GL_FLOAT, GL_FALSE, 0, 0);                   
                } else {
                    std::cout << "Not supported vertex property type";
                }
                glBindBuffer(GL_ARRAY_BUFFER, 0);
            }

            std::vector<Int3> mesh_triangles = mesh->GetTriangles();

            std::vector<unsigned int> mesh_indicies = { };
            for (int k = 0; k < mesh_triangles.size(); k++) { 
                mesh_indicies.push_back(mesh_triangles[k].x);
                mesh_indicies.push_back(mesh_triangles[k].y);
                mesh_indicies.push_back(mesh_triangles[k].z);
                new_mesh.TriangleSize++;
            }

            glGenBuffers(1, &new_mesh.MeshIBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, new_mesh.MeshIBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mesh_indicies), &mesh_indicies[0], GL_STATIC_DRAW);

            mesh->SetPlatformMesh(new_mesh);
        }
    };
}
