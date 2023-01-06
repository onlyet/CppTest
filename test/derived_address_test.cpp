#include "common.h"

struct parent
{
    int a;
    bool b;
    int c;

    virtual void print() {}
};

struct child : public parent
{
    int d;
    void print() override {}
};


void derived_struct_test()
{
    child foo;
    cout << (int)&foo << endl;
    cout << (int)&foo.a << endl;
    cout << (int)&foo.b << endl;
    cout << (int)&foo.c << endl;
    cout << (int)&foo.d << endl;

    //parent* p = new child;
    //cout << (int)p << endl;
    //cout << (int)&p->a << endl;
    //cout << (int)&p->b << endl;
    //cout << (int)&p->c << endl;

}