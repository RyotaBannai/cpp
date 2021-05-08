#include <array>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void use()
{
  string s{"1,3,4, 5,6, 67"};
  regex pat{R"(\s*,\s*)"};
  copy(sregex_token_iterator{s.begin(), s.end(), pat, -1}, sregex_token_iterator{},
       ostream_iterator<string>{cout, "\n"});
}

void use_split()
{
  string input{"x 1 x2 10 x3 20"};
  regex pat{R"((\w+)\s(\d+))"};
  string format{"$1,$2\n"};
  string out = regex_replace(input, pat, format, regex_constants::format_no_copy);

  regex delim_ln{R"(\s*\n\s*)"};
  regex delim_comma{R"(\s*,\s*)"};
  vector<string> v{};
  copy(sregex_token_iterator{out.begin(), out.end(), delim_ln, -1}, sregex_token_iterator{},
       std::back_inserter(v));

  for (auto x : v)
    cout << x << endl;
}

int main()
{
  // use();
  use_split();
}