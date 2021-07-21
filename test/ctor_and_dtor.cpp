#include "ctor_and_dtor.h"
//
//CtorAndDtor::CtorAndDtor()
//{
//}
//
//CtorAndDtor::~CtorAndDtor()
//{
//}
//
//void ctor_and_dtor_demo()
//{
//    CtorAndDtor obj;
//    CtorAndDtor* pObj = new CtorAndDtor;
//    delete pObj;
//}//#include "ctor_and_dtor.h"
//
//CtorAndDtor::CtorAndDtor()
//{
//}
//
//CtorAndDtor::~CtorAndDtor()
//{
//}
//
//void ctor_and_dtor_demo()
//{
//    CtorAndDtor obj;
//    CtorAndDtor* pObj = new CtorAndDtor;
//    delete pObj;
//}

void derive_test()
{
    //Base b = Derive();
    Derive d;
    Base b;
    b = d;
    //Derive d(Derive());
}
