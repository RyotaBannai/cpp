class Foo
{
public:
  Foo(int foo) : m_foo(foo){};
  int get_foo() { return m_foo; }

private:
  int m_foo;
};

void do_bar(Foo foo)
{
  int i = foo.get_foo();
}

int main()
{
  do_bar(1);
  /* if you pass string you'll get 'error: no matching function for call to 'do_bar',
  note: candidate function not viable: no known conversion from 'const char [1]' to 'Foo' for 1st argument

  if you prefix Foo constructor with explicit,  you'll get note:
  note: candidate function not viable: no known conversion from 'int' to 'Foo' for 1st argument
  */

  return 0;
}