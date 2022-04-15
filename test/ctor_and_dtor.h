#pragma once
#include <iostream>

using namespace std;

//class Base
//{
//public:
//    Base() { cout << "Base()" << endl; }
//    Base(const Base&) { cout << "Base(const Base&)" << endl; }
//    ~Base() { cout << "~Base()" << endl; }
//};
//
//class Derive : public Base
//{
//public:
//    Derive() { cout << "Derive()" << endl; }
//    Derive(const Derive&) { cout << "Derive(const Derive&)" << endl; }
//    ~Derive() { cout << "~Derive()" << endl; }
//};


class parent;
class parent {
public:
    virtual void eat(/*Base* b*/) {
        cout << "parent" << endl;
        //cout << "parent friendfunc: " << b->i << endl;
    }
};

class son {
public:
    virtual void eat(/*Base* b*/) {
        cout << "son" << endl;
        //cout << "parent friendfunc: " << b->i << endl;
    }
};

class Base
{
public:
    Base() 
        //: i(0)
    { 
        cout << "Base()" << endl;
        vf();
    }
    virtual ~Base() { 
        cout << "~Base()" << endl; 
        vf();
    }
     virtual void vf() { cout << "Base virtual func" << endl; }

     //friend virtual void friendfunc(Base* b);
     friend void parent::eat(/*Base* b*/);
     //friend virtual void tt() {};
    int i = 1;
};




//void friendfunc(Base* b)
//{
//    cout << "friendfunc: " << b->i << endl;
//}

class Derive : public Base
{
public:
    Derive() { 
        cout << "Derive()" << endl; 
    }
    ~Derive() { 
        cout << "~Derive()" << endl; 
    }

    void vf() override { cout << "Derive virtual func" << endl; }

    //inline virtual   void tt() {}

};

void derive_test();
