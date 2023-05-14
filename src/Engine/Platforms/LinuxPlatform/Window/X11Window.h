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
        XEvent event;
    public:
        PlatformWindow(WindowData data, EventSystem* event) {
            this->windowData = data;

            dis = XOpenDisplay((char *)0);
            screen = DefaultScreen(dis);
        
            win = XCreateSimpleWindow(dis, DefaultRootWindow(dis), 0, 0, data.WindowSize.x, data.WindowSize.y, 5, BlackPixel(dis, screen), WhitePixel(dis, screen));
            XSetStandardProperties(dis, win, data.WindowName, data.WindowName, None, NULL, 0, NULL);
            gc = XCreateGC(dis, win, 0, 0);
            XSelectInput(dis, win, NoEventMask | ExposureMask | ButtonPressMask | KeyPressMask);
            XSetBackground(dis, gc, WhitePixel(dis, screen));
            XSetForeground(dis, gc, BlackPixel(dis, screen));

            XClearWindow(dis, win);
            XMapRaised(dis, win);

            event->RegisterWindow(this);
        }

        virtual void Open() override {
            XClearWindow(dis, win);
            XMapRaised(dis, win);
        }

        virtual void HandleEvents() override {
            XNextEvent(dis, &event);
            if(event.type==Expose) {
                XClearWindow(dis, win);
            }
            return;
        }

        virtual void Close() override {
            XFreeGC(dis, gc);
            XDestroyWindow(dis, win);
            XCloseDisplay(dis);
        }
    };
}