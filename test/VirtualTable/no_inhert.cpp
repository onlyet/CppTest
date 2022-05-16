#if 0
#include <iostream>

using namespace std;

class NoInhert_A {
public:
    NoInhert_A() { cout << "NoInhert_A::NoInhert_A()" << endl; }
    virtual ~NoInhert_A() { cout << "NoInhert_A::~NoInhert_A()" << endl; }
    virtual void f() { cout << "NoInhert_A::f()" << endl; }
    virtual void g() { cout << "NoInhert_A::g()" << endl; }
    intptr_t a = 1;
};

void foo() { cout << "foo()" << endl; }

void tt() {
    void (NoInhert_A::*pMember)() = &NoInhert_A::g;
    // 非成员函数加不加&都可以
    void (*pNonMember)() = foo;

    NoInhert_A obj;
    //(obj.*pMember)();

    // 两种方式调用非成员函数都可以
    //pNonMember();
    //(*pNonMember)();
}

int main() {
    tt();
    return 0;
}
#endif