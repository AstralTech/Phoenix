file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")

add_executable(PhoenixApp ${SOURCE_FILES})
target_include_directories(PhoenixApp PUBLIC ../Gryphon/)

target_link_libraries(PhoenixApp GryphonEngine)