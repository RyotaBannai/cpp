#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class My_money_io : public moneypunct<char, true> {
public:
  explicit My_money_io(size_t r = 0) : moneypunct<char, true>(r) {}
  using char_type = char;
  using string_type = basic_string<char_type>;
  using pattern = money_base::pattern;

protected:
  char_type do_decimal_point() const override { return '.'; };
  char_type do_thousands_sep() const override { return ','; }
  string_type do_grouping() const override { return "\003"; } // 数値を３桁の文字ごとにグルーピング
  string_type do_curr_symbol() const { return "USD "; }

  string_type do_positive_sign() const { return ""; }
  string_type do_negative_sign() const { return "()"; }

  int do_frac_digits() const { return "()"; }

  pattern do_pos_format() const { return pat; }
  pattern do_neg_format() const { return pat; }

private:
  static const pattern pat;
};

const pattern My_money::pat{sign, symbol, value, none};

void use() {}

int main() { use(); }