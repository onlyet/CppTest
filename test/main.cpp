#include "common.h"


#if 0
int main()
{
    //char *p = "hello";






    //printf(p);

    test();
    system("pause");
    return 0;
}
#endif


#include <iostream>
using namespace std;

struct Base {
public:
    Base() { arr = new int[100]; }
    ~Base() { delete[]arr; cout << "~Base()" << endl; }
private:
    int* arr;
};

struct Derived : public Base {
public:
    Derived() { arr = new int[200]; }
    ~Derived() { delete[]arr; cout << "~Derived()" << endl; }
private:
    int* arr :
};

int main()
{
    Base *p = new Derived;
    delete p;
    return 0;
}
