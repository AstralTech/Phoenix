#pragma once

#include "GL/glew.h"

#include "../../Platforms/Platform.h"
#include "iostream"

#include "../../Core/Threading/Systems/RenderingSystem/RenderBuffer.h"
#include "OpenGLRenderBuffer.h"

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
        unsigned int vao;
        unsigned int buffer;
        unsigned int shader;

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
            
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            glGenBuffers(1, &buffer);
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
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

            shader = CreateShader(vertexShader, fragmentShader);
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

            glBindVertexArray(vao);
            glUseProgram(shader);
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
    };
}
