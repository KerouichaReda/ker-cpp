cmake_minimum_required(VERSION 3.14.0 )
project(example LANGUAGES CXX)

SET(PROJECT_SOURCE_FILES
container/dynamic_array.cc
)


add_executable(example ${PROJECT_SOURCE_FILES})

target_link_libraries(example PRIVATE ker::ker )
