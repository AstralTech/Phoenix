#pragma once

#include "GL/glew.h"

#include "../../Platforms/Platform.h"
#include "iostream"

#include "../../Core/Threading/Systems/RenderingSystem/RenderBuffer.h"

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

    struct PlatformRenderBuffer {
    public:
        unsigned int framebuffer;
        unsigned int textureColorbuffer;
        unsigned int rbo;
    public:
        PlatformRenderBuffer(RenderBuffer* buffer) {
            glGenFramebuffers(1, &framebuffer); 

            // generate texture
            glGenTextures(1, &textureColorbuffer);
            glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, buffer->RenderBufferSize.x, buffer->RenderBufferSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

            // attach it to currently bound framebuffer object
            glGenRenderbuffers(1, &rbo);
            glBindRenderbuffer(GL_RENDERBUFFER, rbo); 
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, buffer->RenderBufferSize.x, buffer->RenderBufferSize.y);  

            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);   
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0); 
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

            if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
            else
                std::cout << "Created a framebuffer\n";
        }

        void Bind() {
            std::cout << "Binding framebuffer: " << framebuffer << "\n";

            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        }

        void BindForRendering() {
            std::cout << "Frame buffer texture: " << textureColorbuffer << "\n";

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
        }
    };

    class RendererLink {
    public:
        unsigned int vao;
        unsigned int buffer;
        unsigned int shader;

        unsigned int current_frame_buffer = 0;
    public:
        void Init() {
            float vertex[24] = {
                -0.5,  0.5, 0.0, 0.0,
                -0.5, -0.5, 0.0, 1.0,
                 0.5, -0.5, 1.0, 1.0,

                -0.5,  0.5, 0.0, 0.0,
                 0.5,  0.5, 1.0, 0.0,
                 0.5, -0.5, 1.0, 1.0
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

            glBindVertexArray(vao);
            glUseProgram(shader);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            glEnable(GL_DEPTH_TEST);

            std::cout << "Drawing Buffer: " << buffer->framebuffer << "\n";
        }

        // Renderer Rendering Routines
        void ClearScreen(float r, float g, float b, float a) {
            glBindFramebuffer(GL_FRAMEBUFFER, current_frame_buffer);

            glClearColor(r, g, b, a);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            std::cout << "Clearing Frame buffer\n";
        }
    };
}
