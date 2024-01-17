cmake_minimum_required(VERSION 3.15)
project(ker-cpp VERSION 0.0.1 LANGUAGES CXX)

add_library(ker INTERFACE)
add_library(ker::ker ALIAS ker)


target_include_directories( 
  ker INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
  )

target_compile_features(ker INTERFACE cxx_std_17)

add_subdirectory(example)
add_subdirectory(include)
