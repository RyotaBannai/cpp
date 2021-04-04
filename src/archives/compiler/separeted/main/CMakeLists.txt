# a.out をターゲットと呼ぶ
add_executable(a.out main.cpp)

target_compile_options(a.out PUBLIC -O2 -Wall)
target_compile_features(a.out PUBLIC cxx_std_17)
target_compile_definitions(a.out PUBLIC NDEBUG _USE_MATH_DEFINES)
target_link_libraries(a.out libs)