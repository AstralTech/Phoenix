#include "Settings.h"

#include "Gryphon.h"
#include "Phoenix.h"

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