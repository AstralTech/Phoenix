#pragma once

#include "Settings.h"

#if (GRYPHON_OS == WINDOWS)
#include "WindowsPlatform/Windows.h"
#elif (GRYPHON_OS == LINUX) 
#include "LinuxPlatform/Linux.h"
#elif (GRYPHON_OS == MACOS)
#include "MacOSPlatform/MacOS.h"
#endif