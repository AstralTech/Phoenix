# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gregory/Projects/Applications/PhoenixEditor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gregory/Projects/Applications/PhoenixEditor/build

# Include any dependencies generated for this target.
include Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/compiler_depend.make

# Include the progress variables for this target.
include Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/progress.make

# Include the compile flags for this target's objects.
include Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/flags.make

Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/src/main.cpp.o: Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/flags.make
Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/src/main.cpp.o: /home/gregory/Projects/Applications/PhoenixEditor/Projects/PhoenixApp/src/main.cpp
Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/src/main.cpp.o: Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gregory/Projects/Applications/PhoenixEditor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/src/main.cpp.o"
	cd /home/gregory/Projects/Applications/PhoenixEditor/build/Projects/PhoenixApp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/src/main.cpp.o -MF CMakeFiles/PhoenixApp.dir/src/main.cpp.o.d -o CMakeFiles/PhoenixApp.dir/src/main.cpp.o -c /home/gregory/Projects/Applications/PhoenixEditor/Projects/PhoenixApp/src/main.cpp

Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PhoenixApp.dir/src/main.cpp.i"
	cd /home/gregory/Projects/Applications/PhoenixEditor/build/Projects/PhoenixApp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gregory/Projects/Applications/PhoenixEditor/Projects/PhoenixApp/src/main.cpp > CMakeFiles/PhoenixApp.dir/src/main.cpp.i

Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PhoenixApp.dir/src/main.cpp.s"
	cd /home/gregory/Projects/Applications/PhoenixEditor/build/Projects/PhoenixApp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gregory/Projects/Applications/PhoenixEditor/Projects/PhoenixApp/src/main.cpp -o CMakeFiles/PhoenixApp.dir/src/main.cpp.s

Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/src/main/PhoenixApplication.cpp.o: Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/flags.make
Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/src/main/PhoenixApplication.cpp.o: /home/gregory/Projects/Applications/PhoenixEditor/Projects/PhoenixApp/src/main/PhoenixApplication.cpp
Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/src/main/PhoenixApplication.cpp.o: Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gregory/Projects/Applications/PhoenixEditor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/src/main/PhoenixApplication.cpp.o"
	cd /home/gregory/Projects/Applications/PhoenixEditor/build/Projects/PhoenixApp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/src/main/PhoenixApplication.cpp.o -MF CMakeFiles/PhoenixApp.dir/src/main/PhoenixApplication.cpp.o.d -o CMakeFiles/PhoenixApp.dir/src/main/PhoenixApplication.cpp.o -c /home/gregory/Projects/Applications/PhoenixEditor/Projects/PhoenixApp/src/main/PhoenixApplication.cpp

Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/src/main/PhoenixApplication.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PhoenixApp.dir/src/main/PhoenixApplication.cpp.i"
	cd /home/gregory/Projects/Applications/PhoenixEditor/build/Projects/PhoenixApp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gregory/Projects/Applications/PhoenixEditor/Projects/PhoenixApp/src/main/PhoenixApplication.cpp > CMakeFiles/PhoenixApp.dir/src/main/PhoenixApplication.cpp.i

Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/src/main/PhoenixApplication.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PhoenixApp.dir/src/main/PhoenixApplication.cpp.s"
	cd /home/gregory/Projects/Applications/PhoenixEditor/build/Projects/PhoenixApp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gregory/Projects/Applications/PhoenixEditor/Projects/PhoenixApp/src/main/PhoenixApplication.cpp -o CMakeFiles/PhoenixApp.dir/src/main/PhoenixApplication.cpp.s

# Object files for target PhoenixApp
PhoenixApp_OBJECTS = \
"CMakeFiles/PhoenixApp.dir/src/main.cpp.o" \
"CMakeFiles/PhoenixApp.dir/src/main/PhoenixApplication.cpp.o"

# External object files for target PhoenixApp
PhoenixApp_EXTERNAL_OBJECTS =

Projects/PhoenixApp/PhoenixApp: Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/src/main.cpp.o
Projects/PhoenixApp/PhoenixApp: Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/src/main/PhoenixApplication.cpp.o
Projects/PhoenixApp/PhoenixApp: Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/build.make
Projects/PhoenixApp/PhoenixApp: Projects/Gryphon/libGryphonEngine.a
Projects/PhoenixApp/PhoenixApp: Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gregory/Projects/Applications/PhoenixEditor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable PhoenixApp"
	cd /home/gregory/Projects/Applications/PhoenixEditor/build/Projects/PhoenixApp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PhoenixApp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/build: Projects/PhoenixApp/PhoenixApp
.PHONY : Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/build

Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/clean:
	cd /home/gregory/Projects/Applications/PhoenixEditor/build/Projects/PhoenixApp && $(CMAKE_COMMAND) -P CMakeFiles/PhoenixApp.dir/cmake_clean.cmake
.PHONY : Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/clean

Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/depend:
	cd /home/gregory/Projects/Applications/PhoenixEditor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gregory/Projects/Applications/PhoenixEditor /home/gregory/Projects/Applications/PhoenixEditor/Projects/PhoenixApp /home/gregory/Projects/Applications/PhoenixEditor/build /home/gregory/Projects/Applications/PhoenixEditor/build/Projects/PhoenixApp /home/gregory/Projects/Applications/PhoenixEditor/build/Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Projects/PhoenixApp/CMakeFiles/PhoenixApp.dir/depend

