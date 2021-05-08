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
  ifstream in("file.txt");
  if (!in)
    cerr << "no such file.\n";

  regex pat{R"(\w{2}\s*(\d{5})(-\d{4})?)"};
  cout << pat.mark_count() << endl; // マークされた部分表現の個数

  int lineno = 0;
  for (string line; getline(in, line);) {
    cout << ++lineno << ". target: '" << line << "'\n";
    smatch matches; // 一致した文字列の格納先
    if (regex_search(line, matches, pat)) {
      // 完全一致
      cout << ": '" << matches[0] << "'\n";
      if (1 < matches.size() && matches[1].matched)
        // 部分一致 matches は match_results で sub_match を持つコンテナ
        cout << "\t: '" << matches[1] << "'"
             << ", len: " << matches.length(1) << '\n'; // equivalent to matches[1].length()
    }
  }
}

void use_replace()
{
  string input{"x 1 x2 10 x3 20"};
  regex pat{R"((\w+)\s(\d+))"};
  string format{"{$1, $2}\n"};
  cout << regex_replace(input, pat, format, regex_constants::format_no_copy);
}

// for string delimiter
vector<string> split(string s, string delimiter)
{
  size_t pos_start = 0, pos_end, delim_len = delimiter.length();
  string token;
  vector<string> res;

  while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
    token = s.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    res.push_back(token);
  }

  res.push_back(s.substr(pos_start));
  return res;
}

template <std::size_t... S, typename T>
void unpack_vector(const vector<T> &vec, std::index_sequence<S...>)
{
  // test2(vec[S]...);
}

template <std::size_t size, typename T> void unpack_vector(const vector<T> &vec)
{
  cout << vec.size() << endl;
  if (vec.size() != size)
    throw new exception() /* choose your error */;
  unpack_vector(vec, std::make_index_sequence<size>());
}

void use_replace_then_parse()
{
  string input{"x 1 x2 10 x3 20"};
  regex pat{R"((\w+)\s(\d+))"};
  string format{"$1,$2\n"};
  string out = regex_replace(input, pat, format, regex_constants::format_no_copy);

  map<string, int> new_m;
  for (auto x : split(out, "\n"))
    unpack_vector<2>(split(x, ","));
  // unpack_vector<2>(vector<string>{"a", "b"});
  // cout << typeid(x).name() << endl;
  // new_m.emplace_back(split(x, ",")...);

  // for (auto m : new_m)
  //   cout << m << endl;
}

int main()
{
  // use();
  // use_replace();
  use_replace_then_parse();
}