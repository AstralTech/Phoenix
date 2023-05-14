#include "Settings.h"

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