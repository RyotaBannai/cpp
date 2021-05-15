#include <cerrno>
#include <cmath>
#include <iostream>
using namespace std;

/**
 * does not work.
 */
void use()
{
  errno = 0;
  sqrt(-1);
  if (errno == EDOM)
    cerr << "sqrt() not defined for negative arg.";

  pow(numeric_limits<double>::max(), 2);
  if (errno == ERANGE)
    cerr << "result of pow() too large to represent as a double.";
}
int main() { use(); }