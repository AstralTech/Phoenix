#pragma once

namespace Engine
{
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
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, buffer->RenderBufferSize.x, buffer->RenderBufferSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
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
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        }

        void BindForRendering() {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
        }
    };   
} // namespace Engine
