// 菱形继承

#if 0
#include <iostream>

using namespace std;

/**
 * @brief 16字节
 * vptr_A
 * a
*/
class A {
public:
    A() { cout << "A::A()" << endl; }
    virtual ~A() { cout << "A::~A()" << endl; }
    virtual void f() { cout << "A::f()" << endl; }
    intptr_t a = 1;
};

/**
 * @brief 24字节
 * vptr_B
 * a
 * b
*/
class B : public A {
public:
    B() { cout << "B::B()" << endl; }
    virtual ~B() { cout << "B::~B()" << endl; }
    virtual void g() { cout << "B::g()" << endl; }
    intptr_t b = 2;
};

/**
 * @brief 24字节
 * vptr_C
 * a
 * c
*/
class C : public A {
public:
    C() { cout << "C::C()" << endl; }
    virtual ~C() { cout << "C::~C()" << endl; }
    virtual void h() { cout << "C::h()" << endl; }
    intptr_t c = 3;
};

/**
 * @brief 56字节
 * --------------------
 * vptr_B
 * a
 * b
 * --------------------
 * vptr_C
 * a
 * c
 * --------------------
 * d
*/
class Tom : public B, public C {
public:
    Tom() { cout << "Tom::Tom()" << endl; }
    virtual ~Tom() { cout << "Tom::~Tom()" << endl; }
    void f() override { cout << "Tom::f()" << endl; }
    virtual void k() { cout << "Tom::k()" << endl; }
    intptr_t d = 4;
};

int main() {
    Tom t;
    //t.a = 2;
    return 0;
}
#endif