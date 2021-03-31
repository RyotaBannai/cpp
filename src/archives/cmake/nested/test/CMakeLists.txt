# set(Boost_DEBUG 1) # check if where cmake is looking for Boost

find_package(Boost REQUIRED)
message( ${CMAKE_CURRENT_SOURCE_DIR} ) # Display message
message( ${Boost_FOUND} )
IF (Boost_FOUND)
    # message (${Boost_VERSION})
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()


# a.out をターゲットと呼ぶ
add_executable(a.out main.cpp)

# CMAKE_CXX_FLAGS の使用の代わりに推奨されている手法
# might better way to specify version instead of add Flags https://stackoverflow.com/questions/10851247/how-do-i-activate-c-11-in-cmake
target_compile_options(a.out PUBLIC -O2 -Wall)
target_compile_features(a.out PUBLIC cxx_std_17) # C++ 14 を使用
target_compile_definitions(a.out PUBLIC NDEBUG _USE_MATH_DEFINES)

# greetings 共有ライブラリを a.out にリンクする
target_link_libraries(a.out greetings)
target_link_libraries(a.out ${Boost_LIBRARIES} )