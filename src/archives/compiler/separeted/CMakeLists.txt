cmake_minimum_required(VERSION 2.8)

project(calculation, CXX)

add_executable(a.out main.cpp error.cpp lexer.cpp parser.cpp table.cpp)

target_compile_options(a.out PUBLIC -O2 -Wall)
target_compile_features(a.out PUBLIC cxx_std_17) # C++ 14 を使用
target_compile_definitions(a.out PUBLIC NDEBUG _USE_MATH_DEFINES)