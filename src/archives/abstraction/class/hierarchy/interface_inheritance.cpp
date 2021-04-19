#include <iostream>
#include <new>
#include <string>
#include <list>
#include <vector>
#include <complex>
using namespace std;

class Ival_box {
  virtual int get_value() = 0;
  virtual void set_value() = 0;
  virtual void reset_value() = 0;
  virtual void prompt() = 0;
  virtual void was_changed() = 0;
  virtual ~Ival_box() {};
};

class BBwidget {
protected:
  virtual void mouse1hit() = 0;
}

// multiple inheritance
class Ival_slider : public Ival_box, protected BBwidget {
public:
  Ival_slider(int, int);
  ~Ival_slider() override;

  int get_value() override;
  void set_value(int i) override;

protected:
  // ... BBiedget の仮想関数をオーバーライドする関数
  // 例えば、BBwidget::draw() や　BBwidget::mouse1hit() など...
  void mouse1hit() override;
private:
  // slider に必要なデータ
  int current_height{ 0 };
}

int main() {
  return 0;
}