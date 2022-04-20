#pragma once
#include "common.h"

/**
 * @brief 8字节
 * vptr_A
 * a
*/
class VA {
public:
    VA() { cout << "VA::VA()" << endl; }
    virtual ~VA() { cout << "VA::~VA()" << endl; }
    virtual void f() { cout << "VA::f()" << endl; }
    int a = 1;
};

/**
 * @brief 12字节
 * vptr_B
 * a
 * b
*/
class VB : virtual public VA {
public:
    VB() { cout << "VB::VB()" << endl; }
    virtual ~VB() { cout << "VB::~VB()" << endl; }
    virtual void g() { cout << "VB::g()" << endl; }
    int b = 2;
};

/**
 * @brief 12字节
 * vptr_C
 * a
 * c
*/
class VC : virtual public VA {
public:
    VC() { cout << "VC::VC()" << endl; }
    virtual ~VC() { cout << "VC::~VC()" << endl; }
    virtual void h() { cout << "VC::h()" << endl; }
    int c = 3;
};

/**
 * @brief 28字节
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
class VTom : public VB, public VC {
public:
    VTom() { cout << "VTom::VTom()" << endl; }
    virtual ~VTom() { cout << "VTom::~VTom()" << endl; }
    void f() override { cout << "VTom::f()" << endl; }
    virtual void k() { cout << "VTom::k()" << endl; }
    int d = 4;
};
