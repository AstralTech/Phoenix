// --------------------------------Defines------------------------------------
#define ENGINE_OS_LINUX
#define LINUXOS_WINDOWING_SYSTEM X11 // Tells me to not use wayland because im lazy as shit and dont want to support it
// ---------------------------------------------------------------------------

#include "Engine/Engine.h"
#include "PhoenixApp/Phoenix.h"

int main() {
    Phoenix::PhoenixApplication* app = new Phoenix::PhoenixApplication();
    app->Init();

    app->RunApp();
    while (app->IsRunning()) {
        std::cout << std::flush;
        app->UpdateApp();
    }

    app->CloseApp();

    return 0;
}