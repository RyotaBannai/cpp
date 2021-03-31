# CMake のバージョンを設定
cmake_minimum_required(VERSION 2.8)

# プロジェクト名と使用する言語を設定
project(test_project, CXX)

# a.out という実行ファイルを main.cpp と hello.cpp から作成
# separate files by white shpace
add_executable(a.out main.cpp hello.cpp)