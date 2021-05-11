#include <array>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

/**
 * 特定の locale に対する Season の入手力表現するためには、Season_id の派生クラスを作成して、適切な
 * to_str(), from_str() を定義するとよい.
 *
 */
enum Season { spring, summer, fall, winter };
class Season_io : public locale::facet {
public:
  Season_io(int i = 0) : locale::facet{i} {};
  ~Season_io(){}; // Season_io オブジェクトを解体可能にする
  virtual const string &to_str(Season x) const = 0;

  virtual bool from_str(const string &s, Season &x) const = 0;
  static locale::id id;
};

locale::id Seasons_id::id; // 識別子オブジェクトを定義

// out
ostream &operator<<(ostream &os, Season x)
{
  // ストリームが Season_io 特殊項目を持っていれば、Season の値を文字列に変換
  locale loc{os.getloc()};
  if (has_face<Season_io>(loc))
    return os << use_facet<Season_io>(loc).to_str(x);
  return os << static_case<int>(x);
}

// in
istream &operator>>(istream &is, Season &x)
{
  const locale &loc{is.getloc()};
  if (has_facet<Season_io>(loc)) {
    const Season_io &f{use_facet<Season_io>(loc)};
    string buf;
    if (!(is >> buf && f.from_str(buf, x))) // 文字列表現を読み取る
      is.setstate(ios_base::faibait) return is; // 入力表現が選択されている locale での Season
                                                // を正しく表現していなければ、ストリームは、fail
                                                // 状態に遷移
  }

  int i;
  is >> i;
  x = static_cast<Season>(i);
  return is;
}

void use() {}

int main()
{
  // use();
}