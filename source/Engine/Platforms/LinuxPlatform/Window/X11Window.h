#pragma once
#include "iostream"

#include "../../../Core/Window/Window.h"

#include "X11/Xlib.h"
#include "X11/Xutil.h"
#include "X11/Xos.h"

namespace Engine {
    class PlatformWindow : public ApplicationWindow {
    private:
        Display *dis;
        int screen;
        Window win;
        GC gc;
    public:
        PlatformWindow(WindowData data) {
            this->windowData = data;

            dis = XOpenDisplay((char *)0);
            screen = DefaultScreen(dis);
            win = XCreateSimpleWindow(dis, DefaultRootWindow(dis), 0, 0, data.WindowSize.x, data.WindowSize.y, 5, 0, 0);
            XSetStandardProperties(dis, win, data.WindowName, data.WindowName, None, NULL, 0, NULL);
            gc = XCreateGC(dis, win, 0, 0);
            XSetBackground(dis, gc, 0);
            XSetForeground(dis, gc, 0);
            XClearWindow(dis, win);
            XMapRaised(dis, win);
        }

        virtual void Open() override {
            
        }

        virtual void Update() override {
            XClearWindow(dis, win);
        }

        virtual void Close() override {
            XFreeGC(dis, gc);
            XDestroyWindow(dis, win);
            XCloseDisplay(dis);
        }
    };
}