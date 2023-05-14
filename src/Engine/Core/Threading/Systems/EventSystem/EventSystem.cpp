#include "EventSystem.h"
#include "iostream"

#include "../../../../Platforms/Platform.h"

namespace Engine {
    void EventSystem::RegisterWindow(PlatformWindow* win) {
        windows_open.push_back(win);
    }


    void EventSystem::OnStart() {
        
    }
    void EventSystem::OnUpdate() {
        for (int i = 0; i < windows_open.size(); i++) {
            windows_open[i]->HandleEvents();
        }
    }
    void EventSystem::OnEnd() {

    }
}   