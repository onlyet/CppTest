#if 0

#include <iostream>
#include <stdio.h>
#include <stdint.h>

using namespace std;

class B
{
public:
    int ib;
public:
    B(int i = 1) :ib(i) {}
    virtual ~B() { cout << "B::~B()" << endl; }
    virtual void f() { cout << "B::f()" << endl; }
    virtual void Bf() { cout << "B::Bf()" << endl; }
};

class B1 : virtual public B
{
public:
    int ib1;
public:
    B1(int i = 100) :ib1(i) {}
    virtual ~B1() { cout << "B1::~B1()" << endl; }
    virtual void f() { cout << "B1::f()" << endl; }
    virtual void f1() { cout << "B1::f1()" << endl; }
    virtual void Bf1() { cout << "B1::Bf1()" << endl; }
};

#if 0
class B2 : public B

{

public:

    int ib2;

public:

    B2(int i = 1000) :ib2(i) {}

    virtual void f() { cout << "B2::f()" << endl; }

    virtual void f2() { cout << "B2::f2()" << endl; }

    virtual void Bf2() { cout << "B2::Bf2()" << endl; }

};


class D : public B1, public B2

{

public:

    int id;



public:

    D(int i = 10000) :id(i) {}

    virtual void f() { cout << "D::f()" << endl; }

    virtual void f1() { cout << "D::f1()" << endl; }

    virtual void f2() { cout << "D::f2()" << endl; }

    virtual void Df() { cout << "D::Df()" << endl; }

};
#endif

typedef void(*Fun)(void);

class Man {
public:
    Man() { cout << "Man::Man" << endl; };
    virtual ~Man() { cout << "Man::~Man" << endl; };
    virtual void play() { cout << "Man::play" << endl; }
};
void tt() {}
int q;
int w = 1;
const char *u = "hello"; // 带不带const结果都一样
const int e3 = 666888;
int main()
{
    int e;
    int r = 2;
    int *t = new int(3);
    const char *y = "hello"; 
    const int e2 = 4;

    cout << "tt " << (int*)tt << endl;          // 0x400946 .text
    //cout << "tt " << reinterpret_cast<int*>(tt) << endl;          // 0x400946 .text
    // SO上说打印成员函数指针会引入UB？
    //printf("B::f: %p\n", (void*)&B::f);         // 0x400b56 .text
    //printf("B::f: %p\n", &B::f);         // 0x400b56 .text
    printf("y: %p\n", y);                       // 0x401218 .rodata 字符串常量位于.rodata，地址接近代码段
    printf("u: %p\n", u);                       // 0x401218 .rodata 字符串常量位于.rodata
    cout << "&e3: " << &e3 << endl;             // 0x401220 .rodata 全局const变量位于.rodata，通过objdump打印是位于.rodata
    cout << "&w: " << &w << endl;               // 0x601078 .data
    cout << "&q: " << &q << endl;               // 0x601194 .bss
    cout << "t: " << t << endl;                 // 0xcb9c20 heap
    cout << "&e: " << &e << endl;               // 0x7fff3f4946b4 stack
    cout << "&r: " << &r << endl;               // 0x7fff3f4946b8 stack
    cout << "&y: " << &y << "\t" << y << endl;  // 0x7fff3f4946c8 stack y这个变量位于栈上。y的值是地址，位于.rodata

    cout << "&e2: " << &e2 << endl;             // 0x7fff3f4946bc stack


    Man m;
    intptr_t* pm = (intptr_t*)(*((intptr_t *)&m + 0)) + 2;
    cout << "pm: " << pm << endl;
    cout << "*pm: " << hex << *pm << endl;
    Fun fun = (Fun)(*pm);
    fun();

    // B1 a;
    // cout << sizeof(B) << endl;
    // cout << "B1对象内存大小为：" << sizeof(a) << endl;

    // cout << "[0]B1::vptr";
    // cout << "\t地址：" << /*(int*)*/(&a) << endl;

    // //输出虚表B1::vptr中的函数
    // for (int i = 0; i < 2; ++i)
    // {
    //     cout << "  [" << i << "]";
    //     Fun fun1 = (Fun) * ((int*)*(int*)(&a) + i);
    //     fun1();
    //     cout << "\t地址：\t" << (int*)*((int*)*(int*)(&a) + i) << endl;
    // }

    // //[1]
    // cout << "[1]vbptr ";
    // cout << "\t地址：" << (int*)(&a) + 1 << endl;  //虚表指针的地址
    // //输出虚基类指针条目所指的内容
    // for (int i = 0; i < 2; i++)
    // {
    //     cout << "  [" << i << "]";

    //     cout << *(int*)((int*)*((int*)(&a) + 1) + i);

    //     cout << endl;
    // }


    // //[2]
    // cout << "[2]B1::ib1=" << *(int*)((int*)(&a) + 2);
    // cout << "\t地址：" << (int*)(&a) + 2;
    // cout << endl;

    // //[3]
    // cout << "[3]值=" << *(int*)((int*)(&a) + 3);
    // cout << "\t\t地址：" << (int*)(&a) + 3;
    // cout << endl;

    // //[4]
    // cout << "[4]B::vptr";
    // cout << "\t地址：" << (int*)(&a) + 4 << endl;

    // //输出B::vptr中的虚函数
    // for (int i = 0; i < 2; ++i)
    // {
    //     cout << "  [" << i << "]";
    //     Fun fun1 = (Fun) * ((int*)*((int*)(&a) + 4) + i);
    //     fun1();
    //     cout << "\t地址:\t" << *((int*)*((int*)(&a) + 4) + i) << endl;
    // }

    // //[5]
    // cout << "[5]B::ib=" << *(int*)((int*)(&a) + 5);
    // cout << "\t地址: " << (int*)(&a) + 5;
    // cout << endl;
}

#endif