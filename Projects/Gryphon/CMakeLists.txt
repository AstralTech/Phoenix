file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")

add_library(GryphonEngine ${SOURCE_FILES} ../../Depends/GLEW/src/glew.c)
target_include_directories(GryphonEngine PUBLIC ../../Depends/GLEW/include/ ../../Global/)

target_link_libraries(GryphonEngine GL dl X11) 