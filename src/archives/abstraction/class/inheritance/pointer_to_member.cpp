#include <iostream>
#include <new>
#include <string>
#include <list>
#include <vector>
#include <complex>
using namespace std;


class Std_interface {
public:
  virtual void start() = 0;
  virtual void suspend() = 0;
  virtual void resume() = 0;
  virtual void quit() = 0;
  virtual void full_size() = 0;
  virtual void small() = 0;

  virtual ~Std_interface() {};
};

// use public inheritance when derived class needs to to casted to base class
class Std_concrete : public Std_interface {
public:
  Std_concrete() {}
  void start() {};
  void suspend();
  void resume() {};
  void quit() {};
  void full_size() {};
  void small() {};

  ~Std_concrete() {};
};

void Std_concrete::suspend() {
  cout << "call Std_concrete::suspend()" << endl;
};

using Pstd_mem = void(Std_interface::*)(); // あらゆるメンバへのポインタ型　

/*
Firstly, this is a pointer, meaning you have to apply ->* to it, but not .*.
If you want to use .*, you have to dereference this with * first.

Secondly, function call operator () has higher priority than .* or ->* operators,
meaning that you need extra parentheses to make sure that the pointer f is dereferenced first,
and the function call () is applied to the result of that dereference.
*/
void use(Std_interface* p) {
  Pstd_mem s = &Std_interface::suspend; // suspend() へのポインタ
  p->suspend(); // そのまま呼び出す
  (p->*s)(); // メンバへのポインタ経由で呼び出す
}

class Task {
public:
  Task() = default;
  static void schddule() {
    cout << "call Task::scheule()" << endl;
  };
};

int main() {
  Std_concrete c{};
  use(&c);
  void (*p)() = &Task::schddule; // 通常の関数へのポインタ // static の場合のみ有効. 特定のオブジェクトに結びづけられていないため(610)
  p();
  // void (Task:: * pm)() = &Task::schddule; // static の場合エラー
  // error: cannot initialize a variable of type 'void (Task::*)()' with an rvalue of type 'void (*)()'
  return 0;
}