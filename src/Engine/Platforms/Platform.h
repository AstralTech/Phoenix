#pragma once

#include "../../Settings.h"

#define WINDOWS 0
#define LINUX 1
#define MACOS 2

#if (ENGINE_OS == WINDOWS)
#include "WindowsPlatform/Windows.h"
#elif (ENGINE_OS == LINUX) 
#include "LinuxPlatform/Linux.h"
#elif (ENGINE_OS == MACOS)
#include "MacOSPlatform/MacOS.h"
#endif