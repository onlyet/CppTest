#include "common.h"
#include "std_future_demo.h"

#include <string>
#include <future>
#include <iostream>

using namespace std;

void X::foo(int n, std::string const &s)
{
    cout << "X::foo, n = " << n << ", s = " << s << endl;
}

std::string X::bar(std::string const &s)
{
    cout << "X::bar, " << "s = " << s << endl;
    return s;
}

Y::Y()
{
    cout << "Y::Y()" << endl;
}

Y::Y(const Y &)
{
    cout << "Y::Y(const Y&)" << endl;
}

Y::Y(Y &&)
{
    cout << "Y::Y(Y&&)" << endl;
}

double Y::operator()(double n)
{
    cout << "Y::operator(), " << n << endl;
    return n;
}

move_only::move_only()
{

}

move_only::move_only(move_only &&)
{
    cout << "move_only::move_only(move_only &&)" << endl;
}

move_only & move_only::operator=(move_only &&)
{
    return *this;
}

void move_only::operator()()
{
}


void future_demo()
{
    X x;
    //auto f1 = std::async(&X::foo, &x, 42, "hello");  // 调用p->foo(42, "hello")，p是指向x的指针
    //auto f2 = std::async(&X::bar, x, "goodbye");  // 调用tmpx.bar("goodbye")， tmpx是x的拷贝副本

    //Y y;
    //auto f3 = std::async(Y(), 3.141);  // 调用tmpy(3.141)，tmpy通过Y的移动构造函数得到
    //auto f4 = std::async(std::ref(y), 2.718);  // 调用y(2.718)

    std::async(baz, std::ref(x));  // 调用baz(x)

    auto f5 = std::async(move_only());  // 调用tmp()，tmp是通过std::move(move_only())构造得到


}

X baz(X &x)
{
    return X();
}
