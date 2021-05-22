#include <future>
#include <iostream>
#include <thread>
#include <utility>

using namespace std;

int calc()
{
  int sum = 0;
  for (int i = 0; i < 10; ++i) {
    sum += i + 1;
  }
  return sum;
}

void use()
{
  packaged_task<int()> task(calc); // 非同期実行する関数を登録する
  future<int> f = task.get_future();

  // 別スレッドで計算を行う
  thread t(move(task));
  t.detach();

  try {
    // 非同期処理の結果値を取得する
    cout << f.get() << endl;
  }
  catch (...) {
    // 非同期実行している関数内で投げられた例外を捕捉
  }
}

int ff(int i)
{
  if (i)
    return i;
  throw runtime_error("ff(0)");
}

void use2()
{
  packaged_task<int(int)> pt1{ff};
  packaged_task<int(int)> pt2{ff};

  future<int> f1 = pt1.get_future();
  future<int> f2 = pt2.get_future();

  pt1(1);
  pt2(0); // exception で処理が落ちない点に注目.

  try {
    cout << f1.get() << '\n';
    cout << f2.get() << '\n';
  }
  catch (exception &e) {
    cout << "exception: " << e.what() << '\n';
  }
}

int main()
{
  // use();
  use2();
}