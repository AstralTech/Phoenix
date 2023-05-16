#pragma once

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>

#include "iostream"

namespace Engine {
    class PlatformWindowManager {
    public:
        Display* display;
        Screen* screen;
        int screenId;
    public:
        PlatformWindowManager() {
        // Open the display
            // display = XOpenDisplay(NULL);
            // if (display == NULL) {
            //     std::cout <<  "Could not open display";
            // }
            // screen = DefaultScreenOfDisplay(display);
            // screenId = DefaultScreen(display);
        }
    };

    class PlatformWindow {
    private:
        Window window;
        XEvent ev;
        Atom atomWmDeleteWindow;

        Display* display;
        Screen* screen;
        int screenId;

        PlatformWindowManager* platformWindowManager;

        bool isClosed = false;
    public:
        bool IsClosed() { return isClosed; }

        PlatformWindow(PlatformWindowManager* vplatformWindowManager, const char* WindowName, int xSize, int ySize) {
            //platformWindowManager = vplatformWindowManager;

            display = XOpenDisplay(NULL);
            if (display == NULL) {
                std::cout <<  "Could not open display";
            }
            screen = DefaultScreenOfDisplay(display);
            screenId = DefaultScreen(display);
            
            window = XCreateSimpleWindow(display, RootWindowOfScreen(screen), 0, 0, xSize, ySize, 1, BlackPixel(display, screenId), WhitePixel(display, screenId));
            XSelectInput(display, window, KeyPressMask | KeyReleaseMask | ExposureMask);
            XStoreName(display, window, WindowName);

            atomWmDeleteWindow = XInternAtom(display, "WM_DELETE_WINDOW", False);
            XSetWMProtocols(display, window, &atomWmDeleteWindow, 1);

            // Show the window
            XClearWindow(display, window);
            XMapRaised(display, window);
        }

        void UpdatePlatformWindow() {
            if (IsClosed())
                return;
        }

        void ManageWindowEvents() {
            std::cout << "Handaling Event\n";

            XNextEvent(display, &ev);
            if (ev.type == Expose) {
                XClearWindow(display, window);
            }
            if (ev.type == ClientMessage) {
				if (ev.xclient.data.l[0] == atomWmDeleteWindow) {
					CloseWindow();
				}
			}
			else if (ev.type == DestroyNotify) { 
				CloseWindow();
			}
        }

        void CloseWindow() {
            XDestroyWindow(display, window);
            XFree(screen); 
            XCloseDisplay(display);
            isClosed = true;           
        }
    };
}
