#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Some_error {
};

void taskmaster()
{
  try {
    auto result = do_task();
  }
  catch (Some_error) {
    // fails to do do_task()
  }
}

int do_task()
{
  int result{1};
  if (true) {
    return result;
  }
  else {
    throw Some_error{};
  }
}

int main()
{
  taskmaster();
  return 0;
}