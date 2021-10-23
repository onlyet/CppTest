//#include "common.h"


#if 0
//#if 1
//int main()
//{
//    test();
//    system("pause");
//    return 0;
//}
//#endif


#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void GetMemory(char* p)
{
    p = (char*)malloc(100);
}
int main()
{
    //char *p = "hello";






    //printf(p);

    test();
    system("pause");
    //char* str = NULL;
    const char* str = "HELLO";
    //GetMemory(str);
    //strcpy(str, "hello world");
    printf("str:%s\n", str);
    printf(str);
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
}