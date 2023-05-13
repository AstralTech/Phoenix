#pragma once

#ifdef ENGINE_OS_WINDOWS
#include "WindowsPlatform/Windows.h"
#else 
    #ifdef ENGINE_OS_LINUX
    #include "LinuxPlatform/Linux.h"
    #else
        #ifdef ENGINE_OS_MACOS
        #include "MacOSPlatform/MacOS.h"
        #else
        #include "LinuxPlatform/Linux.h"
        #endif
    #endif
#endif