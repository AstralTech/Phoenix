# include "LinuxPlatformWindow.h"
#include "Settings.h"

#if GRYPHON_OS == LINUX
namespace Engine {

    static Bool IsXEvent
    (Display* xDisplay, XEvent* xEvent, XPointer arg)
    {
        return True;
    }

    void PlatformWindowManager::UpdateEventQueue() {
        int event = 0;

        XLockDisplay(display);
        if (XCheckIfEvent(display, &ev, IsXEvent, NULL)) {
            Window evWindow = ev.xany.window;
            for (int i = 0; i < windows.size(); i++) {
                if (windows[i]->window == evWindow) {
                    windows[i]->ManageWindowEvents(ev);
                }
            }
        }
        XUnlockDisplay(display);
    }

    void PlatformWindowManager::RegisterWindow(PlatformWindow* window) {
            windows.push_back(window);

            if (windows.size() > 1)
                return;

            glXMakeCurrent(display, window->window, context);

            GLenum err = glewInit();
            if (GLEW_OK != err){
                std::cout << glewGetErrorString(err);
            }
    }
}
#endif