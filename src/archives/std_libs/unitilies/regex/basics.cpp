#include <ctype.h>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
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

int main() { use(); }