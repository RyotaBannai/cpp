#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class My_punct : public numpunct<char> {
public:
  explicit My_punct(size_t r = 0) : numpunct<char>(r) {}
  using char_type = char;
  using string_type = basic_string<char_type>;

protected:
  char_type do_decimal_point() const override { return ','; };
  char_type do_thousands_sep() const override { return '_'; }
  string do_grouping() const override { return "\003"; } // 数値を３桁の文字ごとにグルーピングする

  // string_type do_truename() const; // default is 1, may change to true
  // string_type do_falsename() const; // default is 0, may change to false
};

void use()
{
  cout << "style A: " << 12345678 << " *** " << 1234567.8 << " *** " << fixed << 1234567.8 << '\n';
  cout << defaultfloat; // 小数点の書式をリセット
  locale loc(locale(), new My_punct);
  cout.imbue(loc); // imbue は解体された後も、stream の中に存在し続ける.(1132)
  cout << "style B: " << 12345678 << " *** " << 1234567.8 << " *** " << fixed << 1234567.8 << '\n';
  /**
   * style A: 12345678***1.23457e+06***1234567.800000
   * style B: 12_345_678***1,23457e+06***1_234_567,800000
   */
}

int main() { use(); }