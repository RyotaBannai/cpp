# greeings をターゲットと呼ぶ
# add_library で　main の CMakeLists.txt で依存ライブラリとして、target_link_libraries で追加できるようにする
add_library(greetings SHARED hello.cpp good_morning.cpp)
target_include_directories(greetings PUBLIC ${PROJECT_SOURCE_DIR}/include)