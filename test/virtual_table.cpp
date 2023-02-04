#include "common.h"
#include "virtual_inhert.h"

//// 8字节
//class Base1 {
//public:
//    Base1() { cout << "Base1::Base1()" << endl; }
//    virtual ~Base1() { cout << "Base1::~Base1()" << endl; }
//    virtual void f() { cout << "Base1::f()" << endl; }
//    virtual void g() { cout << "Base1::g()" << endl; }
//    int a = 1;
//};
//
//// 8字节
//class Base2 {
//public:
//    Base2() { cout << "Base2::Base2()" << endl; }
//    virtual ~Base2() { cout << "Base2::~Base2()" << endl; }
//    virtual void f() { cout << "Base2::f()" << endl; }
//    virtual void g() { cout << "Base2::g()" << endl; }
//    virtual void h() { cout << "Base2::h()" << endl; }
//    int b = 2;
//};
//
//// 20字节
//class Derived : public Base1, public Base2 {
//public:
//    Derived() { cout << "Derived::Derived()" << endl; }
//    virtual ~Derived() { cout << "Derived::~Derived()" << endl; }
//    void f() override { cout << "Derived::f()" << endl; }
//    void h() override { cout << "Derived::h()" << endl; }
//    virtual void k() { cout << "Derived::k()" << endl; }
//    int c = 3;
//};
//
//typedef void(*Fcn)();
//void printDerived(Derived& d)
//{
//    cout << endl << "print all vtable:" << endl;
//    cout << endl;
//    int i = 0, j = 1;
//
//    while (i < 2) {
//        //Fcn vfcn = (Fcn) * ((int*)(*((int*)&d + i)) + j);
//        //cout << sizeof(Base1) << endl;
//        Fcn vfcn = (Fcn) * ((intptr_t*)(*(intptr_t*)((char*)&d + i * sizeof(Base1))) + j);
//        cout << "Base" << i + 1 << "::vtable:" << endl;
//        while (/*vfcn*/j < 4) {
//            // 两种方式调用都可以
//            vfcn();
//            //(*vfcn)();
//            ++j;
//            vfcn = (Fcn) * ((intptr_t*)(*(intptr_t*)((char*)&d + i * sizeof(Base1))) + j);
//        }
//        ++i;
//        j = 1;
//
//        cout << endl;
//    }
//}
//
//void print_vtbl_address(Derived& d)
//{
//    cout << endl;
//    int i = 0, j = 0;
//    while (i < 2) {
//        //cout << hex << *((int*)&d + i) << endl;
//        //printf("(int*)&d + %d: %x\n", i, (int*)&d + i);
//        printf("虚表指针 *((int*)&d + %d): %x\n", i, *((int*)&d + i));
//
//        Fcn vfcn = (Fcn) * ((intptr_t*)(*((intptr_t*)&d + i)) + j);
//        cout << "Base" << i + 1 << "::vtable:" << endl;
//        while (vfcn) {
//            //printf("(int*)(*((int*)&d + %d)) + %d: %x\n", i, j, (int*)(*((int*)&d + i)) + j);
//            printf("虚函数地址 *((int*)(*((int*)&d + %d)) + %d): %Ix\n", i, j, *((intptr_t*)(*((intptr_t*)&d + i)) + j));
//
//            ++j;
//            vfcn = (Fcn) * ((intptr_t*)(*((intptr_t*)&d + i)) + j);
//        }
//        ++i;
//        j = 0;
//
//        cout << endl;
//    }
//}

//#if 1
///**
// * @brief 8字节
// * vptr_A
// * a
//*/
//class A {
//public:
//    A() { cout << "A::A()" << endl; }
//    virtual ~A() { cout << "A::~A()" << endl; }
//    virtual void f() { cout << "A::f()" << endl; }
//    int a = 1;
//};
//
///**
// * @brief 12字节
// * vptr_B
// * a
// * b
//*/
//class B : public A {
//public:
//    B() { cout << "B::B()" << endl; }
//    virtual ~B() { cout << "B::~B()" << endl; }
//    virtual void g() { cout << "B::g()" << endl; }
//    int b = 2;
//};
//
///**
// * @brief 12字节
// * vptr_C
// * a
// * c
//*/
//class C : public A {
//public:
//    C() { cout << "C::C()" << endl; }
//    virtual ~C() { cout << "C::~C()" << endl; }
//    virtual void h() { cout << "C::h()" << endl; }
//    int c = 3;
//};
//
///**
// * @brief 28字节
// * --------------------
// * vptr_B
// * a
// * b
// * --------------------
// * vptr_C
// * a
// * c
// * --------------------
// * d
//*/
//class Tom : public B, public C {
//public:
//    Tom() { cout << "Tom::Tom()" << endl; }
//    virtual ~Tom() { cout << "Tom::~Tom()" << endl; }
//    void f() override { cout << "Tom::f()" << endl; }
//    virtual void k() { cout << "Tom::k()" << endl; }
//    int d = 4;
//};
//#endif





void test_vtbl()
{
    // 多重继承
    //Derived d;
    //printDerived(d);
    //print_vtbl_address(d);

    //*(int*)((char*)&d+8)

    // 菱形继承
    //Tom d;
    //d.B::f();
    //cout << sizeof(A) << sizeof(B) << sizeof(C) << sizeof(Tom) << endl;
    //cout << d.B::a << endl;
    //cout << d.C::a << endl;
    //d.B::a = 2;
    //cout << d.B::a << endl;
    //cout << d.C::a << endl;

    cout << endl;

    // 虚继承
    //VTom v;
    //cout << sizeof(VA) << sizeof(VB) << sizeof(VC) << sizeof(VTom) << endl;
}
