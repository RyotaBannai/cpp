#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// mbstate_t: <cwchar> と <wchar.h> が定義する mbstate_t 型はそのシスてもで標準となる char と
// wchar_t の変換方法を表す. 実行マシンごとに適切に定義がされている(1149)
template <typename State> class Cvt_to_upper : public codecvt<char, char, mbstate_t> {
public:
  explicit Cvt_to_upper(size_t r = 0) : codecvt(r) {}
  using E = char;

protected:
  // 外部の文字表現を読み取って、内部の文字表現を書き出す
  result do_in(State &s, const char *from, const char *from_end, const char *&from_next, char *to,
               char *to_end, char *&to_next) const override;
  // 内部の文字表現を読み取って外部の文字表現を書き出す
  result do_out(State &s, const char *from, const char *from_end, const char *&from_next, char *to,
                char *to_end, char *&to_next) const override;

  result do_unshift(State &, E *to, E *to_end, E *&to_next) const override { return ok; }

  int do_encoding() const noexcept override { return 1; }
  bool do_always_noconv() const noexcept override { return false; }

  int do_length(const State &, const E *from, const E *from_end, size_t max) const override;
};

codecvt<char, char, mbstate_t>::result Cvt_to_upper::do_out(State &s, const char *from,
                                                            const char *from_end,
                                                            const char *&from_next, char *to,
                                                            char *to_end, char *&to_next) const
{
  return codecvt<char, char, mbstate_t>::do_out(s, from, from_end, from_next, to, to_end, to_next);
}

codecvt<char, char, mbstate_t>::result Cvt_to_upper::do_in(State &s, const char *from,
                                                           const char *from_end,
                                                           const char *&from_next, char *to,
                                                           char *to_end, char *&to_next) const
{
  return codecvt<char, char, mbstate_t>::do_in(s, from, from_end, from_next, to, to_end, to_next);
}

void use()
{
  locale uloc(locale(), new Cvt_to_upper);

  cin.imbue(uloc);
  for (char ch : cin >> ch)
    cout << ch;
}

int main() { use(); }