#include "error.hpp"

int Error::no_of_errors;
double Error::error(const string &s)
{
  no_of_errors++;
  cerr << "error: " << s << endl;
  return 1;
};