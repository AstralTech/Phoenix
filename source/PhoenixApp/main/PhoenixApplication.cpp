#include "PhoenixApplication.h"
#include "iostream"

namespace Phoenix {
    void PhoenixApplication::RunApp() {
        std::cout << "Starting the Application on " << platform->GetName() << " hope this goes well";

        // Create my window and shiz see mom i dont curse in my code
        main_window = platform->CreateWindow(Engine::WindowData(
            "Phoenix Text Editor [v0.01][x86]",
            Int2(1280, 720)
        ));
        main_window->Open();
    }

    double clockToMilliseconds(clock_t ticks){
        // units/(units/time) => time (seconds) * 1000 = milliseconds
        return (ticks/(double)CLOCKS_PER_SEC)*1000.0;
    }

    clock_t deltaTime = 0;
    unsigned int frames = 0;
    double  frameRate = 30;
    double  averageFrameTimeMilliseconds = 33.333;

    void PhoenixApplication::UpdateApp() {
        main_window->Update();

        clock_t beginFrame = clock();
        clock_t endFrame = clock();

        deltaTime += endFrame - beginFrame;
        frames ++;

        //if you really want FPS
        if( clockToMilliseconds(deltaTime)>1000.0){ //every second
            frameRate = (double)frames*0.5 +  frameRate*0.5; //more stable
            frames = 0;
            deltaTime -= CLOCKS_PER_SEC;
            averageFrameTimeMilliseconds  = 1000.0/(frameRate==0?0.001:frameRate);

            std::cout<<"CPU time was:"<<averageFrameTimeMilliseconds<<std::endl;
        }
    }

    void PhoenixApplication::CloseApp() {
        main_window->Close();
    }
}