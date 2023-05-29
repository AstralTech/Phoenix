#pragma once

#include "GL/glew.h"

#include "../../Platforms/Platform.h"
#include "iostream"

#include "../../Core/Threading/Systems/RenderingSystem/RenderBuffer.h"
#include "OpenGLRenderBuffer.h"
#include "OpenGLMeshBuilder.h"
#include "OpenGLMesh.h"

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
                    vTexCoord = texCoord;

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

                void main() {

                    gl_Position = vec4(position, 0.0, 1.0);
                }
            )";

            std::string fragmentShader2 = R"(
                #version 330 core

                layout(location = 0) out vec4 color;

                void main() {
                    color = vec4(1.0, 1.0, 1.0, 1.0);
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
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void BuildPlatformMesh(Mesh* mesh) {
            PlatformMesh new_mesh = PlatformMesh();

            float vertex[6] = {
                -0.5, -0.5,
                 0.5, -0.5,
                 0.0,  0.5
            };
            
            glGenVertexArrays(1, &new_mesh.MeshVAO);
            glBindVertexArray(new_mesh.MeshVAO);

            glGenBuffers(1, &new_mesh.MeshVBO);
            glBindBuffer(GL_ARRAY_BUFFER, new_mesh.MeshVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, vertex, GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

            mesh->SetPlatformMesh(new_mesh);
        }
    };
}
