#pragma once
#include "iostream"

#include "../../../Core/Window/Window.h"

#include "X11/Xlib.h"
#include "X11/Xutil.h"
#include "X11/Xos.h"
#include <X11/keysymdef.h>

#include <GL/gl.h>
#include <GL/glx.h>

typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

static bool isExtensionSupported(const char *extList, const char *extension) {
	return strstr(extList, extension) != 0;
}

namespace Engine {
    class PlatformWindow : public ApplicationWindow {
    private:
        Display *display;
        int screenID;
        Screen* screen;
        Window window;
        XEvent ev;
        Atom atomWmDeleteWindow;
        GLXContext context;
        XVisualInfo* visual;
        XSetWindowAttributes windowAttribs;

        bool repaint_aval = false;
    public:
        PlatformWindow(WindowData data, EventSystem* event) {
            this->windowData = data;

            display = XOpenDisplay((char *)0);
            if (display == NULL) {
                std::cout << "Could not open display\n";
            }
            screen = DefaultScreenOfDisplay(display);
            screenID = DefaultScreen(display);
        
            GLint majorGLX, minorGLX = 0;
            glXQueryVersion(display, &majorGLX, &minorGLX);
            if (majorGLX <= 1 && minorGLX < 2) {
                std::cout << "GLX 1.2 or greater is required.\n";
                XCloseDisplay(display);
            }

            GLint glxAttribs[] = {
                GLX_X_RENDERABLE    , True,
                GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
                GLX_RENDER_TYPE     , GLX_RGBA_BIT,
                GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
                GLX_RED_SIZE        , 8,
                GLX_GREEN_SIZE      , 8,
                GLX_BLUE_SIZE       , 8,
                GLX_ALPHA_SIZE      , 8,
                GLX_DEPTH_SIZE      , 24,
                GLX_STENCIL_SIZE    , 8,
                GLX_DOUBLEBUFFER    , True,
                None
            };
            
            int fbcount;
            GLXFBConfig* fbc = glXChooseFBConfig(display, screenID, glxAttribs, &fbcount);
            if (fbc == 0) {
                std::cout << "Failed to retrieve framebuffer.\n";
                XCloseDisplay(display);
            }

            // Pick the FB config/visual with the most samples per pixel
            int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;
            for (int i = 0; i < fbcount; ++i) {
                XVisualInfo *vi = glXGetVisualFromFBConfig( display, fbc[i] );
                if ( vi != 0) {
                    int samp_buf, samples;
                    glXGetFBConfigAttrib( display, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf );
                    glXGetFBConfigAttrib( display, fbc[i], GLX_SAMPLES       , &samples  );

                    if ( best_fbc < 0 || (samp_buf && samples > best_num_samp) ) {
                        best_fbc = i;
                        best_num_samp = samples;
                    }
                    if ( worst_fbc < 0 || !samp_buf || samples < worst_num_samp )
                        worst_fbc = i;
                    worst_num_samp = samples;
                }
                XFree( vi );
            }
            GLXFBConfig bestFbc = fbc[ best_fbc ];
            XFree( fbc ); // Make sure to free this!

            visual = glXGetVisualFromFBConfig( display, bestFbc );
            if (visual == 0) {
                std::cout << "Could not create correct visual window.\n";
                XCloseDisplay(display);
            }
            
            if (screenID != visual->screen) {
                std::cout << "screenId(" << screenID << ") does not match visual->screen(" << visual->screen << ").\n";
                XCloseDisplay(display);
            }

            // Open the window
            windowAttribs.border_pixel = BlackPixel(display, screenID);
            windowAttribs.background_pixel = WhitePixel(display, screenID);
            windowAttribs.override_redirect = True;
            windowAttribs.colormap = XCreateColormap(display, RootWindow(display, screenID), visual->visual, AllocNone);
            windowAttribs.event_mask = ExposureMask;
            window = XCreateWindow(display, RootWindow(display, screenID), 0, 0, data.WindowSize.x, data.WindowSize.y, 0, visual->depth, InputOutput, visual->visual, CWBackPixel | CWColormap | CWBorderPixel | CWEventMask, &windowAttribs);
            XStoreName(display, window, data.WindowName);

            // Redirect Close
            atomWmDeleteWindow = XInternAtom(display, "WM_DELETE_WINDOW", False);
            XSetWMProtocols(display, window, &atomWmDeleteWindow, 1);

            // Create GLX OpenGL context
            glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
            glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc) glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB" );
            
            int context_attribs[] = {
                GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
                GLX_CONTEXT_MINOR_VERSION_ARB, 2,
                GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
                None
            };

            context = 0;
            const char *glxExts = glXQueryExtensionsString( display,  screenID );
            if (!isExtensionSupported( glxExts, "GLX_ARB_create_context")) {
                std::cout << "GLX_ARB_create_context not supported\n";
                context = glXCreateNewContext( display, bestFbc, GLX_RGBA_TYPE, 0, True );
            }
            else {
                context = glXCreateContextAttribsARB( display, bestFbc, 0, true, context_attribs );
            }
            XSync( display, False );

            // Verifying that context is a direct context
            if (!glXIsDirect (display, context)) {
                std::cout << "Indirect GLX rendering context obtained\n";
            }
            else {
                std::cout << "Direct GLX rendering context obtained\n";
            }
            glXMakeCurrent(display, window, context);

            std::cout << "GL Renderer: " << glGetString(GL_RENDERER) << "\n";
            std::cout << "GL Version: " << glGetString(GL_VERSION) << "\n";
            std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";

            //XClearWindow(display, window);
            XMapRaised(display, window);

            event->RegisterWindow(this);
        }

        virtual void Open() override {

        }

        virtual void HandleEvents() override {
            if (XPending(display) > 0) {
                XNextEvent(display, &ev);
                if (ev.type == Expose) {
                    XWindowAttributes attribs;
                    XGetWindowAttributes(display, window, &attribs);
                    repaint_aval = true;
                }
                // if (ev.type == ClientMessage) {
                //     if (ev.xclient.data.l[0] == atomWmDeleteWindow) {
                //         is_open = false;
                //     }
                // }
                // else if (ev.type == DestroyNotify) { 
                //     is_open = false;
                // }
            }

            return;
        }

        virtual void Render() override {
            if (repaint_aval) {
                std::cout << "PAINTING\n";
                repaint_aval = false;
            } else {
                glXMakeCurrent(display, window, context);
                glClear(GL_COLOR_BUFFER_BIT);

                glXSwapBuffers(display, window);
            }
        }

        virtual void Close() override {
            // Cleanup GLX
            glXDestroyContext(display, context);

            // Cleanup X11
            XFree(visual);
            XFreeColormap(display, windowAttribs.colormap);
            XDestroyWindow(display, window);
            XCloseDisplay(display);
        }
    };
}