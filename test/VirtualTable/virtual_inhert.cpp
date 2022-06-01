// 虚继承

#if 0

#include <iostream>

using namespace std;

/**
 * @brief 16字节
*/
class VA {
public:
    VA() { cout << "VA::VA()" << endl; }
    virtual ~VA() { cout << "VA::~VA()" << endl; }
    virtual void f() { cout << "VA::f()" << endl; }
    intptr_t a = 111;
};

/**
 * @brief VS2017：40字节，gcc5.4.0：32字节
*/
class VB : virtual public VA {
public:
    VB() { cout << "VB::VB()" << endl; }
    virtual ~VB() { cout << "VB::~VB()" << endl; }
    //void f() override { cout << "VB::f()" << endl; }
    virtual void g() { cout << "VB::g()" << endl; }
    intptr_t b = 222;
};

/**
 * @brief VS2017：40字节，gcc5.4.0：32字节
*/
class VC : virtual public VA {
public:
    VC() { cout << "VC::VC()" << endl; }
    virtual ~VC() { cout << "VC::~VC()" << endl; }
    virtual void h() { cout << "VC::h()" << endl; }
    intptr_t c = 333;
};

/**
 * @brief VS2017：80字节，gcc5.4.0：56字节
 * --------------------
*/
class VTom : public VB, public VC {
public:
    VTom() { cout << "VTom::VTom()" << endl; }
    virtual ~VTom() { cout << "VTom::~VTom()" << endl; }
    void f() override { cout << "VTom::f()" << endl; }
    virtual void k() { cout << "VTom::k()" << endl; }
    intptr_t d = 444;
};

int main() {
    VTom v;
    //cout << sizeof(VA) << endl;
    //cout << sizeof(VB) << endl;
    //cout << sizeof(VC) << endl;
    //cout << sizeof(VTom) << endl;

    //cout << *((intptr_t*)&v + 0) << endl;
    //cout << *((intptr_t*)&v + 1) << endl;
    //cout << *((intptr_t*)&v + 2) << endl;
    //cout << *((intptr_t*)&v + 3) << endl;
    //cout << *((intptr_t*)&v + 4) << endl;
    //cout << *((intptr_t*)&v + 5) << endl;
    //cout << *((intptr_t*)&v + 6) << endl;
    //cout << *((intptr_t*)&v + 7) << endl;

    cout << typeid(v).name() << endl;
    const type_info& tp = typeid(v);
    return 0;
}

#endif