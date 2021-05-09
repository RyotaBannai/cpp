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

template <typename K, typename V> class OMap {
public:
  std::map<K, V> m{};

  template <std::size_t... S, typename T>
  void unpack_vector(const vector<T> &&vec, std::index_sequence<S...>)
  {
    m.emplace(vec[S]...);
  }

  template <typename T> void emplace_from_vec(const vector<T> &&vec)
  {
    unpack_vector(std::forward<decltype(vec)>(vec), make_index_sequence<2>());
  }
};

template <typename K, typename V> ostream &operator<<(ostream &os, const OMap<K, V> &om)
{
  for (const auto &p : om.m)
    os << '{' << p.first << ": " << p.second << "}\n";
  return os;
}

void use_replace_then_parse()
{
  string input{"x 1 x2 10 x3 20"};
  regex pat{R"((\w+)\s(\d+))"};
  string format{"$1,$2\n"};
  string out = regex_replace(input, pat, format, regex_constants::format_no_copy);

  OMap<string, string> new_m;
  for (auto x : split(out, "\n")) {
    new_m.emplace_from_vec(split(x, ","));
  }

  cout << new_m;
}

int main() { use_replace_then_parse(); }