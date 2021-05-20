#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

recursive_mutex cout_mutex;

template <typename Arg> void write(Arg a)
{
  cout_mutex.lock();
  cout << a;
  cout_mutex.unlock();
}

template <typename Arg, typename... Args> void write(Arg a, Args... tail)
{
  cout_mutex.lock();
  cout << a;
  write(tail...);
  cout_mutex.unlock();
}

void use() { write("hello,", "world\n", "hello,", "world\n"); }

int main() { use(); }