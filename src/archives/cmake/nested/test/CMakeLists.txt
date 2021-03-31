# a.out をターゲットと呼ぶ
add_executable(a.out main.cpp)

# greetings 共有ライブラリを a.out にリンクする
target_link_libraries(a.out greetings)