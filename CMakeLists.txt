cmake_minimum_required(VERSION 3.17)

project(Phoenix)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "Projects/PhoenixApp/src/*.h" "Projects/PhoenixApp/src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC Projects/Gryphon/)
add_subdirectory(Projects/Gryphon)


target_link_libraries(${PROJECT_NAME} GL dl X11 GryphonEngine)
