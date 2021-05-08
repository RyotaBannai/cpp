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

template <typename K, typename V> ostream &operator<<(ostream &os, const map<K, V> &m)
{
  for (const auto &p : m)
    os << '{' << p.first << ": " << p.second << "}\n";
  return os;
}

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

/**
 * @brief split with string delimiter
 * https://stackoverflow.com/a/46931770/5590919
 */
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

/**
 * https://stackoverflow.com/questions/41980888/how-to-convert-from-stdvector-to-args
 */

template <std::size_t... S, typename K, typename V, typename T>
void unpack_vector(map<K, V> &m, const vector<T> &vec, std::index_sequence<S...>)
{
  m.emplace(forward<decltype(vec[S])>(vec[S])...);
}

/**
 * @brief push_back new map pair from vector with size of 2(key, value pair)
 * @tparam size length of vector must be two
 * @param m target map
 * @param vec source key-value pair vector
 */
const std::size_t Vec_size = 2;
template <std::size_t size, typename K, typename V, typename T>
void emplace_from_vec(map<K, V> &m, const vector<T> &vec)
{
  if (vec.size() != size)
    // throw; // ? should throw
    return;
  unpack_vector(m, vec, make_index_sequence<2>());
}

void use_replace_then_parse()
{
  string input{"x 1 x2 10 x3 20"};
  regex pat{R"((\w+)\s(\d+))"};
  string format{"$1,$2\n"};
  string out = regex_replace(input, pat, format, regex_constants::format_no_copy);

  map<string, string> new_m;
  for (auto x : split(out, "\n"))
    emplace_from_vec<Vec_size>(new_m, split(x, ","));

  cout << new_m;
}

int main()
{
  // use();
  // use_replace();
  use_replace_then_parse();
}