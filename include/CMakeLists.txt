add_library(ker_lib STATIC

ker/container/dynamic_array.h

)


set_target_properties(ker_lib PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(ker_lib INTERFACE cxx_std_17)