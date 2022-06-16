#if 0

#include<iostream>
//#include <string>
using namespace std;

//class A {
//public:
//    int val;
//    A(int v) : val(v) { cout << "A()" << endl; }
//};
//
//class B {
//public:
//    int val;
//    B(int v) : val(v) { cout << "B()" << endl; }
//};
//
//class C {
//public:
//    A a;
//    B b;
//    C(int a, int b) : b(b), a(a) { cout << "C()" << endl; }
//};
//
//class Foo
//{
//public:
//    int val;
//    Foo* pnext;
//    A a;
//    //Foo(int v) : val(v), pnext(nullptr) {}
//
//    //Foo() : a(5) { }
//};
//void foo_fo() {
//    //string s;
//
//    //Foo fo;
//
//    C c(1,2);
//}


class NoDefault {
public:
    NoDefault(const std::string&) {}
    // additional members follow, but no other constructors
};
struct A { // my_mem is public by default; see ¡ì 7.2 (p. 268)
    NoDefault my_mem /*= string("")*/;
};
A a; // error: cannot synthesize a constructor for A
struct B {
    B() : b_member("") {} // error: no initializer for b_member
    NoDefault b_member /*= string("")*/;
};

int main()
{
    //foo_fo();
    system("pause");
}

#endif