#include <array>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

locale dk{"da_DK"}; // denmark locale（全ての facet を含む）を一度だけ読みとる.
                    //それから dk の locale と必要な facet を利用
void use()
{
  const collate<char> &col{use_facet<collate<char>>(dk)};
  const ctype<char> &ctype{use_facet<ctype<char>>(dk)};

  locale dk1{loc, &col};   // denmark 用文字列比較を利用
  locale dk2{dk1, &ctype}; // denmark 用文字列比較と、文字分類を利用

  sort(v.begin(), b.end(), dk2); // 文字列については denmark だが、数値についてはデフォルトのまま
}

int main() { use(); }