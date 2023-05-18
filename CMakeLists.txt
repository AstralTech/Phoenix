cmake_minimum_required(VERSION 3.17)

project(Phoenix)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES} Depends/GLAD/src/glad.c)
target_include_directories(${PROJECT_NAME} PUBLIC src/)
target_include_directories(${PROJECT_NAME} PUBLIC Depends/GLAD/include/)

target_link_libraries(${PROJECT_NAME} GL dl X11)
