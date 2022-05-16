#if 1
#include <iostream>

using namespace std;

class SingleInhert_A {
public:
    SingleInhert_A() { cout << "SingleInhert_A::SingleInhert_A()" << endl; }
    virtual ~SingleInhert_A() { cout << "SingleInhert_A::~SingleInhert_A()" << endl; }
    virtual void f() { cout << "SingleInhert_A::f()" << endl; }
    virtual void g() { cout << "SingleInhert_A::g()" << endl; }
    intptr_t a = 1;
};

class SingleInhert_B : public SingleInhert_A {
public:
    SingleInhert_B() { cout << "SingleInhert_B::SingleInhert_B()" << endl; }
    virtual ~SingleInhert_B() { cout << "SingleInhert_B::~SingleInhert_B()" << endl; }
    virtual void f() { cout << "SingleInhert_B::f()" << endl; }
    virtual void h() { cout << "SingleInhert_B::h()" << endl; }
    intptr_t b = 2;
};

int main() {
    SingleInhert_B obj;
    return 0;
}
#endif