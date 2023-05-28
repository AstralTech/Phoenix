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

    class RendererLink {
    public:
        unsigned int vao;
        unsigned int buffer;
        unsigned int shader;
    public:
        void Init() {
            float vertex[12] = {
                -0.5,  0.5,
                -0.5, -0.5,
                 0.5, -0.5,

                -0.5,  0.5,
                 0.5,  0.5,
                 0.5, -0.5
            };
            
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            glGenBuffers(1, &buffer);
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertex, GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

            std::string vertexShader = R"(
                #version 330 core

                layout(location = 0) in vec4 position;

                void main() {
                    gl_Position = position;
                }
            )";

            std::string fragmentShader = R"(
                #version 330 core

                layout(location = 0) out vec4 color;

                void main() {
                    color = vec4(0.0, 1.0, 0.0, 1.0);
                }           
            )";

            shader = CreateShader(vertexShader, fragmentShader);


            std::cout << "Finished creating shader thingy";
        }


        void DrawRenderBuffer(RenderBuffer* buffer) {
            glBindVertexArray(vao);
            glUseProgram(shader);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
    };
}
