#include "ctor_and_dtor.h"

using namespace std;

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
    //Base b;
    //b = d;
    //Derive d(Derive());
    
    //{
    //    Derive d;
    //}
    //cout << endl;
    //{
    //    Base* pb = new Derive;
    //    delete pb;
    //}


    //Base b;
    //cout << "sizeof(Base): " << sizeof(b) << endl;
        //Base* pb = new Base;

    
    //friendfunc(&b);
    //tt();


    //unique_ptr<Base> sp1 = make_unique<Derive>();
    shared_ptr<Base> sp2 = make_shared<Derive>();

    cout << endl;
}

