### Links

- [CMake の使い方（その１）](https://qiita.com/shohirose/items/45fb49c6b429e8b204ac)
- [CMake の使い方（その２）](https://qiita.com/shohirose/items/637f4b712893764a7ec1)

### Build

- `in-sourceビルド`: `cmake .` でソースツリーとビルドツリーを同じフォルダに配置するやり方
- `out-of-source`: ソースツリーとビルドツリーを別フォルダに配置するやり方
  - `$ cd {PROJECT_ROOT} && cmake -S . -B build/` OR `$ {PROJECT_ROOT} && cmake -B build/`
  - `$ cd {PROJECT_ROOT}/build && cmake ..`
- [PROJECT_DIR 関連の環境変数](https://qiita.com/osamu0329/items/7de2b190df3cfb4ad0ca#%E3%81%AF%E3%81%98%E3%82%81%E3%81%AB)
- [.cmake](https://gitlab.kitware.com/cmake/community/-/wikis/doc/tutorials/How-to-create-a-ProjectConfig.cmake-file)
- [cmake tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
- [C++応用講座 CMake 編](https://theolizer.com/cpp-school-root/cpp-school3/)

### General

- 親ディレクトリで宣言されている変数はサブディレクト内でも使用できる
- コンパイル環境に応じてオプションを変えたいときは、`if-else` を使うか [`Generator Expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html)を使う
- ライブラリを直接指定せず、`find_package` を使って名前やパスを取得し、`target_link_libraries` に渡してリンクすることもできる
  - `find_package` で利用可能なライブラリ名: `cmake --help-module-list`
  - この場合事前に C++ 依存ライブラリをローカルにインストールしておく必要がある。 例えば、Boost を使いたい場合、brew などで先にインストールしておく
  - それから `find_package` を使うとインストールされうるフォルダを探索し、見つけたライブラリにフォルダ先を環境変数へ追加する.
    - Boost の場合:
      - `Boost_INCLUDE_DIR` 環境変数を追加し、参照先フォルダを追加する
      - `Boost_LIBRARIES` 環境変数を、依存ライブラリとして自前のコードにリンクする
  - [FindBoost](https://cmake.org/cmake/help/latest/module/FindBoost.html)
  - [Add Boost_INCLUDE_DIR stackoverflow](https://stackoverflow.com/questions/3808775/cmake-doesnt-find-boost)
- [Useful Variables](https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/Useful-Variables#)

### 変数を渡して条件分岐で処理する

- 次のように渡して、実行時に引数で渡す: `cmake -DGREETINGS_BUILD_SHARED_LIBS=ON ..`

```cmake
# GREETINGS_BUILD_SHARED_LIBSというオプションを作成。デフォルトをOFFに設定。
option(GREETINGS_BUILD_SHARED_LIBS "build greetings as a shared library" OFF)

if (GREETINGS_BUILD_SHARED_LIBS)
  add_library(greetings SHARED hello.cpp good_morning.cpp)
else()
  add_library(greetings STATIC hello.cpp good_morning.cpp)
endif()
```
