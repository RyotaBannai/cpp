#include <string>
#include <thread>   // std::thread
#include <iostream> // std::out
#include <vector>
#include <functional>
using namespace std;

void f(int x)
{
  cout << "Good, you?\n";
};

class F
{
private:
  vector<double> &v;

public:
  F(vector<double> &vv) : v{vv} {};
  void operator()()
  {
    cout << "Show elems of vector: \n";
    for (auto p = v.begin(); p != v.end(); ++p)
      cout << *p << endl;
  };
};

int main()
{
  vector<double> some_vec = {1.0, 2.0};
  std::thread t1(f, 0);
  std::thread t2{F(some_vec)};

  t1.join();
  t2.join();

  return 0;
}
