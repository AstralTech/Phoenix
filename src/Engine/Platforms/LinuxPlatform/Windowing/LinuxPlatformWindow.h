#pragma once

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>


#include "iostream"
#include <cstring>

#if (ENGINE_RENDERER == OPENGL)
// #include <glad/glad.h>

#include <GL/gl.h>
#include <GL/glx.h>

typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

static bool isExtensionSupported(const char *extList, const char *extension) {
	return strstr(extList, extension) != 0;
}
#endif


#include "../../../Renderers/Renderer.h"


namespace Engine {
    class PlatformWindowManager {
    public:
        Display* display;
        Screen* screen;
        int screenId;
        GLXContext context;

        XVisualInfo* visual;
    public:
        void CreateContext () {
            #ifdef ENGINE_RENDERER == OPENGL
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
                        GLXFBConfig* fbc = glXChooseFBConfig(display, screenId, glxAttribs, &fbcount);
            
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
                    const char *glxExts = glXQueryExtensionsString( display,  screenId );
                    if (!isExtensionSupported( glxExts, "GLX_ARB_create_context")) {
                        std::cout << "GLX_ARB_create_context not supported\n";
                        context = glXCreateNewContext( display, bestFbc, GLX_RGBA_TYPE, 0, True );
                    }
                    else {
                        context = glXCreateContextAttribsARB( display, bestFbc, 0, true, context_attribs );
                    }

                    XSync( display, False );
                #else
                visual = new XVisualInfo();
                visual->depth = DefaultDepthOfScreen(screenId);
                visual->visual = nullptr;
                std::cout << "BRO YOU GUNNA HAVE SOME SERIOUS PROBLEMS";
            #endif
        }

        PlatformWindowManager() {
            XInitThreads();


            // Open the display
            display = XOpenDisplay(NULL);
            if (display == NULL) {
                std::cout <<  "Could not open display";
            }
            screen = DefaultScreenOfDisplay(display);
            screenId = DefaultScreen(display);
            
            #if (ENGINE_RENDERER == OPENGL)
            
            // glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
            // glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc) glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB" );

            // if (!gladLoadGLLoader((GLADloadproc)glXCreateContextAttribsARBProc)) {
            //     std::cout << "Failed to initialize GLAD" << std::endl;
            // }
            #endif

            CreateContext();
        }
    };

    class PlatformWindow {
    private:
        Window window;
        XEvent ev;
        XContext windowContext;
        Atom atomWmDeleteWindow;

        PlatformWindowManager* platformWindowManager;

        bool isClosed = false;

        const char* windowname;
    public:
        bool IsClosed() { return isClosed; }

        PlatformWindow(PlatformWindowManager* vplatformWindowManager, const char* WindowName, int xSize, int ySize) {
            this->windowname = WindowName;
            platformWindowManager = vplatformWindowManager;
            
            XSetWindowAttributes window_attributes;
            window_attributes.border_pixel = 5;
            window_attributes.border_pixel = BlackPixel(platformWindowManager->display, platformWindowManager->screenId);
            window_attributes.override_redirect = True;
            window_attributes.colormap = XCreateColormap(platformWindowManager->display, RootWindow(platformWindowManager->display, platformWindowManager->screenId), platformWindowManager->visual->visual, AllocNone);
            window_attributes.background_pixel = WhitePixel(platformWindowManager->display, platformWindowManager->screenId);
            window_attributes.event_mask = ExposureMask;

            window = XCreateWindow(platformWindowManager->display, RootWindow(platformWindowManager->display, platformWindowManager->screenId)
                , 0, 0, xSize, ySize, 0, platformWindowManager->visual->depth, InputOutput, platformWindowManager->visual->visual, 
                CWBackPixel | CWColormap | CWBorderPixel | CWEventMask, &window_attributes);

            XSelectInput(platformWindowManager->display, window, KeyPressMask | KeyReleaseMask | ExposureMask);
            XStoreName(platformWindowManager->display, window, WindowName);

            atomWmDeleteWindow = XInternAtom(platformWindowManager->display, "WM_DELETE_WINDOW", False);
            XSetWMProtocols(platformWindowManager->display, window, &atomWmDeleteWindow, 1);

            XSaveContext(platformWindowManager->display, window, windowContext, XPointer(this) );

            // Show the window
            XClearWindow(platformWindowManager->display, window);
            XMapRaised(platformWindowManager->display, window);
        }

        void UpdatePlatformWindow() {
            if (IsClosed())
                return;

            #if (ENGINE_RENDERER == OPENGL) 
            glXMakeCurrent(platformWindowManager->display, window, platformWindowManager->context);

            glClearColor(1.0, 1.0, 1.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);

            glXSwapBuffers(platformWindowManager->display, window);
            #endif
        }

        void ManageWindowEvents() {
            if (isClosed)
                return;
            

            XNextEvent(platformWindowManager->display, &ev);

            Window evWindow = ev.xany.window;

            if (ev.type == Expose) {
                XClearWindow(platformWindowManager->display, evWindow);
            }
            if (ev.type == ClientMessage) {
				XDestroyWindow(platformWindowManager->display, evWindow);
                if (evWindow == window) {
                    CloseWindow();
                }
			}
        }

        void CloseWindow() {
            isClosed = true;          
        }
    };
}
