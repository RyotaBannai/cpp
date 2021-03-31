cmake_minimum_required(VERSION 3.2)
project(test_project, CXX)

# オプションの処理が必要な場合は、ディレクトリの先に置く
# set(CMAKE_CXX_FLAGS "-O2 -std=c++11 -Wall") # ビルドオプションを事前に渡すようにする
# 現在は、CMAKE_CXX_FLAGS ではなく、target_compile_options, targer_pompile_features, tearget_compile_definitions を使ってオプションを設定することが推奨されている

# include フォルダは入れない
add_subdirectory(src)
add_subdirectory(test)