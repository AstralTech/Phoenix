file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")

add_library(GryphonEngine ${SOURCE_FILES} ../../Depends/GLAD/src/glad.c)
target_include_directories(GryphonEngine PUBLIC ../../Depends/GLAD/include/ ../../Global/)