#include <iostream>
#include <set>
#include <string>
#include <unordered_set>
using namespace std;

struct Record {
  string name;
  int val;
};

// original hash func
struct Nocase_hash {
  int d = 1;
  size_t operator()(const Record &r) const
  {
    size_t h = 0;
    for (auto c : r.name) {
      h <<= d;
      h ^= toupper(c); // bit-wise opts(266)
    }
    return h;
  }
};

// original equal operator
struct Nocase_equal {
  bool operator()(const Record &a, const Record &b) const
  {
    // cmp their lengths of string.
    if (a.name.size() != b.name.size())
      return false;
    for (int i = 0; i < a.name.size(); ++i)
      if (toupper(a.name[i]) != toupper(b.name[i]))
        return false;
    return true;
  }
};

/**
 * Record の全ての unordered コンテナに対して、hash func, equal opt
 * を一回だけ定義すれば良いように特殊化する
 */
namespace std {
  template <> struct hash<Record> {
    size_t operator()(const Record &r) const { return hash<string>{}(r.name) ^ hash<int>{}(r.val); }
  };
  template <> struct equal_to<Record> {
    bool operator()(const Record &a, const Record &b) const
    {
      return a.name == b.name && a.val == b.val;
    }
  };
}

void use_original_unordered_set()
{
  using My_unordered_set = std::unordered_set<Record, Nocase_hash, Nocase_equal>;
  My_unordered_set s{
      {{"andy", 8}, {"bill", 3}, {"barbara", 12}}, 20, Nocase_hash{2}, Nocase_equal{}};

  // default hash func, equal opt, and 4 backets.
  My_unordered_set s2{{{"andy", 8}, {"bill", 3}, {"barbara", 12}}};

  for (auto r : s) {
    cout << "{" << r.name << "," << r.val << "}\n";
  }

  /** Above usage is redandant.. thus use specialization. */
  unordered_set<Record> ss{{{"andy", 8}, {"bill", 3}, {"barbara", 12}}};
  for (auto r : ss) {
    cout << "{" << r.name << "," << r.val << "}\n";
  }
}
int main() { use_original_unordered_set(); }
