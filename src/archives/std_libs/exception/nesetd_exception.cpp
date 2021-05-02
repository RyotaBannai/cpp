#include <iostream>
#include <string>
using namespace std;

/**
 * throw_with_nested: 現在の exception の上に新しい exception を堆積させて rethrow
 * rethrow_if_nested: 堆積させた exception の下層にさらに exception があれば、それを取り出して throw
 * current_exception: 現在 catch している例外オブジェクトを指すポインタ exception_ptr を取得
 * rethrow_exception: exception_ptr を使用して rethrow . 通常の rethrow は catch の中で throw
 * をする.
 * make_excpetion_ptr: 例外オブジェクトから exception_ptr を構築
 *
 * std::shared_ptr<std::exception> を使う手法もある.
 */
struct Some_error : public runtime_error {
  Some_error(const string &s) : runtime_error(s){};
};

struct My_error : public Some_error {
  My_error(const string &s) : Some_error(s){};
};

void my_code()
{
  try {
    cout << "my_code do something.\n";
    throw My_error{"aaa"};
  }
  catch (exception &e) {
    My_error err{"something went wrong in my code()"};
    throw_with_nested(err);
    // std::rethrow_exception(std::current_exception());
    // std::rethrow_exception(std::make_exception_ptr(e));
  }
}

void user()
{
  try {
    my_code();
  }
  catch (My_error &e) {
    cout << e.what() << endl;
    try {
      rethrow_if_nested(e); // もしあれば、入れ子の例外を再送出.
    }
    catch (Some_error &e) {
      cout << "Some_error occurred.\n";
      cout << e.what() << endl;
    }
  }
  catch (...) {
    cout << "unexpected error." << endl;
  }
}

int main() { user(); }