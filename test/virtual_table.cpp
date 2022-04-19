#include "common.h"

class Base1 {
public:
    Base1() { cout << "Base1::Base1()" << endl; }
    virtual void f() { cout << "Base1::f()" << endl; }
    virtual void g() { cout << "Base1::g()" << endl; }
    //virtual void h() { cout << "Base1::h()" << endl; }
    void tt() { cout << "tt" << endl; }
};

class Base2 {
public:
    Base2() { cout << "Base2::Base2()" << endl; }
    virtual void f() { cout << "Base2::f()" << endl; }
    //virtual void g() { cout << "Base2::g()" << endl; }
    virtual void h() { cout << "Base2::h()" << endl; }
};

class Derived : public Base1, public Base2 {
public:
    Derived() { cout << "Derived::Derived()" << endl; }
    void f() { cout << "Derived::f()" << endl; }
    virtual void g() { cout << "Derived::g()" << endl; }
    virtual void g1() { cout << "Derived::g1()" << endl; }
    virtual void h() { cout << "Derived::h()" << endl; }
};

typedef void(*Fcn)();
void printDerived(Derived& d)
{
    cout << endl << "print all vtable:" << endl;
    cout << endl;
    int i = 0, j = 0;

    while (i < 2) {
        Fcn vfcn = (Fcn) * ((int*)(*((int*)&d + i)) + j);
        cout << "Base" << i + 1 << "::vtable:" << endl;
        while (vfcn) {
            vfcn();
            ++j;
            vfcn = (Fcn) * ((int*)(*((int*)&d + i)) + j);
        }
        ++i;
        j = 0;

        cout << endl;
    }
}

void print_vtbl_address(Derived& d)
{
    cout << endl;
    int i = 0, j = 0;
    while (i < 2) {
        //cout << hex << *((int*)&d + i) << endl;
        //printf("(int*)&d + %d: %x\n", i, (int*)&d + i);
        printf("虚表指针 *((int*)&d + %d): %x\n", i, *((int*)&d + i));

        Fcn vfcn = (Fcn) * ((int*)(*((int*)&d + i)) + j);
        cout << "Base" << i + 1 << "::vtable:" << endl;
        while (vfcn) {
            //printf("(int*)(*((int*)&d + %d)) + %d: %x\n", i, j, (int*)(*((int*)&d + i)) + j);
            printf("虚函数地址 *((int*)(*((int*)&d + %d)) + %d): %x\n", i, j, *((int*)(*((int*)&d + i)) + j));

            ++j;
            vfcn = (Fcn) * ((int*)(*((int*)&d + i)) + j);
        }
        ++i;
        j = 0;

        cout << endl;
    }
}

void test_vtbl()
{
    //Derived d;
    //printDerived(d);
    //print_vtbl_address(d);

    //Base1* p1 = new Derived;
    //p1->f();

    Base2* p2 = new Derived;
    p2->h();
}
