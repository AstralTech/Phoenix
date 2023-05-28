#pragma once
#include "vector"

#include "../../ExecutionManager.h"
#include "../../../../Renderers/Renderer.h"
#include "RenderBuffer.h"

#include "functional"
#include "any"

namespace Engine {
    struct RenderingRenderBuffer {
    public:
        RenderBuffer* renderBuffer;
        PlatformRenderBuffer* platformRenderBuffer;

        bool initilized = false;
    public:
        RenderingRenderBuffer(RenderBuffer* object) {
            this->renderBuffer = object;
        }
    };

    struct RenderCommand {
    public:
        std::string name;
        std::vector<std::any> args;
    };

    struct RenderFrame {
    public:
        std::vector<RenderCommand> commands = {};
    };

    class RenderingSystem : public ExecutionSystem {
    public:
        RendererLink* rendererLink;

        std::vector<RenderingRenderBuffer*> renderBuffers = {};

        RenderingRenderBuffer* GetRenderingRenderBuffer(RenderBuffer* renderBuffer) {
            RenderingRenderBuffer* myRenderingBuffer;
            for (int i = 0; i < renderBuffers.size(); i++) {
                if (renderBuffers[i]->renderBuffer == renderBuffer) {
                    myRenderingBuffer = renderBuffers[i];
                    break;
                }
            }
            return myRenderingBuffer;
        }
    public:
        void RegisterBuffer(RenderBuffer* renderBuffer);

        void DrawRenderBuffer(RenderBuffer* renderBuffer);

        virtual void OnStart()override;
        virtual void OnUpdate() override;
        virtual void OnEnd() override;

        RenderFrame toRenderFrame;
        RenderFrame workingFrame;

        bool working_on_render = false;
    public: 
        // Outward Rendering Routines
        void BindRenderBuffer(RenderBuffer* renderBuffer) {
            RenderCommand bind_buffer_command;
            bind_buffer_command.name = "bind_render_buffer";
            bind_buffer_command.args.push_back(renderBuffer);
            workingFrame.commands.push_back(bind_buffer_command);
        }
        void Clear(Color color) {
            RenderCommand clear_command;
            clear_command.name = "clear_buffer";
            clear_command.args.push_back(color);
            workingFrame.commands.push_back(clear_command);
        }

        void BeginRendererFrame() {
            workingFrame = RenderFrame();
        }

        void EndRendererFrame() {
            while (working_on_render) {}
            toRenderFrame = workingFrame;
        }
    public:
        // Inside Rendering Routines
        void Internal_BindRenderBuffer(RenderBuffer* renderBuffer); // Binds the buffer for rendering
        void Internal_Clear(Color color); // Clears the current render buffer
    };
}