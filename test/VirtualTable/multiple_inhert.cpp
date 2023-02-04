// 多重继承

#if 0

#include <iostream>

using namespace std;

// 16字节
class Base1 {
public:
    Base1() { cout << "Base1::Base1()" << endl; }
    virtual ~Base1() { cout << "Base1::~Base1()" << endl; }
    virtual void f() { cout << "Base1::f()" << endl; }
    virtual void g() { cout << "Base1::g()" << endl; }
    //virtual void j() { cout << "Base1::j()" << endl; }
    intptr_t a = 1;
};

// 16字节
class Base2 {
public:
    Base2() { cout << "Base2::Base2()" << endl; }
    virtual ~Base2() { cout << "Base2::~Base2()" << endl; }
    virtual void f() { cout << "Base2::f()" << endl; }
    virtual void g() { cout << "Base2::g()" << endl; }
    virtual void h() { cout << "Base2::h()" << endl; }
    intptr_t b = 2;
};

// 40字节
class Derived : public Base1, public Base2 {
public:
    Derived() { cout << "Derived::Derived()" << endl; }
    virtual ~Derived() { cout << "Derived::~Derived()" << endl; }
    void f() override { cout << "Derived::f()" << endl; }
    void h() override { cout << "Derived::h()" << endl; }
    virtual void k() { cout << "Derived::k()" << endl; }
    intptr_t c = 3;
};

int main() {
    Derived d;
    //Derived* pd = new Derived;
    //pd->h();
    return 0;
}

#endif
