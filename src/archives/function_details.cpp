#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

void error(int severity, const vector<string> &err)
{
  for (auto &s : err)
    cerr << s << ' ';
  cerr << endl;
  if (severity)
    exit(severity);
}

vector<string> arguments(int argc, char *argv[])
{
  vector<string> res;
  for (int i = 0; i != argc; ++i)
    res.push_back(argv[i]);

  return res;
}

int main(int argc, char *argv[])
{
  auto args = arguments(argc, argv);
  error(args.size() ? 0 : 1, args);

  return 0;
}

/* 
  本当のコンストラクタを一つだけ用意し、処理を一箇所にまとめる方法
*/
class complex
{
  double re, im;

public:
  complex(double r, double i) : re{r}, im{i} {}
  complex(double r) : complex{r, 0} {}
  complex() : complex{0, 0} {}
};

/*
  デフォルト引数を渡すことによってさらに簡潔化させたコンストラクタ
*/
class complex2
{
  double re, im;

public:
  complex2(double r = {}, double i = {}) : re{r}, im{i} {}
};