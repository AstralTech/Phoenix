#pragma once

#include "Settings.h"

#define WINDOWS 0
#define LINUX 1
#define MACOS 2

#if (GRYPHON_OS == WINDOWS)
#include "WindowsPlatform/Windows.h"
#elif (GRYPHON_OS == LINUX) 
#include "LinuxPlatform/Linux.h"
#elif (GRYPHON_OS == MACOS)
#include "MacOSPlatform/MacOS.h"
#endif