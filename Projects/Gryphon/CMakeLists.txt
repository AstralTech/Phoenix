file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")

add_compile_definitions(GLEW_STATIC)

add_library(GryphonEngine ../../Depends/GLEW/src/glew.c ${SOURCE_FILES})
target_include_directories(GryphonEngine PUBLIC ../../Depends/GLEW/include/ ../../Global/)

target_link_libraries(GryphonEngine GLU GL dl X11) 