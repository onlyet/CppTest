#include<iostream>
//#include <string>
using namespace std;

class A {
public:
    int val;
    A(int v) : val(v) { cout << "A()" << endl; }
};

class B {
public:
    int val;
    B(int v) : val(v) { cout << "B()" << endl; }
};

class C {
public:
    A a;
    B b;
    C(int a, int b) : b(b), a(a) { cout << "C()" << endl; }
};

class Foo
{
public:
    int val;
    Foo* pnext;
    A a;
    //Foo(int v) : val(v), pnext(nullptr) {}

    //Foo() : a(5) { }
};
void foo_fo() {
    //string s;

    //Foo fo;

    C c(1,2);
}
int main()
{
    foo_fo();
    system("pause");
}