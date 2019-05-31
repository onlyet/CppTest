#include <iostream>

using namespace std;

class CObject{
    virtual void f() { cout << "CObject::f()" << endl; }
    virtual void g() { cout << "CObject::g()" << endl; }
    virtual void h() { cout << "CObject::h()" << endl; }
};

class CWidget : public CObject {
    virtual void f() { cout << "CWidget::f()" << endl; }
    virtual void g() { cout << "CWidget::g()" << endl; }
    //virtual void h() { cout << "CWidget::h()" << endl; }
};

class CLabel : public CWidget {
    virtual void f() { cout << "CLabel::f()" << endl; }
    //virtual void g() { cout << "CLabel::g()" << endl; }
    //virtual void h() { cout << "CLabel::h()" << endl; }
    virtual void l() { cout << "CLabel::l()" << endl; }
};

using Fcn = void(*)();


//void MutipleLayerDerive()
//{
//    CWidget widget;
//    for (int i = 0; i < 3; ++i)
//    {
//        Fcn fcn = (Fcn)(*((int*)(*((int*)&widget + 0)) + i));
//        fcn();
//    }
//}

void MutipleLayerDerive()
{
    CLabel label;
    for (int i = 0; i < 4; ++i)
    {
        Fcn fcn = (Fcn)(*((int*)(*((int*)&label + 0)) + i));
        fcn();
    }
}


class A {
    virtual void f() { cout << "A::f()" << endl; }
    virtual void g() { cout << "A::g()" << endl; }
    virtual void h() { cout << "A::h()" << endl; }
};

class B : public A {
    virtual void f() { cout << "B::f()" << endl; }
    //virtual void g() { cout << "B::g()" << endl; }
    //virtual void h() { cout << "B::h()" << endl; }
};

class C : public A {
    //virtual void f() { cout << "C::f()" << endl; }
    virtual void g() { cout << "C::g()" << endl; }
    //virtual void h() { cout << "C::h()" << endl; }
};

class D : public B, public C {
    virtual void f() { cout << "D::f()" << endl; }
    //virtual void g() { cout << "D::g()" << endl; }
    //virtual void h() { cout << "D::h()" << endl; }
};

void DiamondDerive()
{
    D d;
    for (int i = 0; i < 3; ++i)
    {
        Fcn fcn = (Fcn)(*((int*)(*((int*)&d + 0)) + i));
        fcn();
    }
    for (int i = 0; i < 3; ++i)
    {
        Fcn fcn = (Fcn)(*((int*)(*((int*)&d + 1)) + i));
        fcn();
    }
}

//int main()
//{
//    MutipleLayerDerive();
//    DiamondDerive();
//
//    system("pause");
//    return 0;
//}