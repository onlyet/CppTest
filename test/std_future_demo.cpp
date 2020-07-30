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
    //auto f1 = std::async(&X::foo, &x, 42, "hello");  // ����p->foo(42, "hello")��p��ָ��x��ָ��
    //auto f2 = std::async(&X::bar, x, "goodbye");  // ����tmpx.bar("goodbye")�� tmpx��x�Ŀ�������

    //Y y;
    //auto f3 = std::async(Y(), 3.141);  // ����tmpy(3.141)��tmpyͨ��Y���ƶ����캯���õ�
    //auto f4 = std::async(std::ref(y), 2.718);  // ����y(2.718)

    std::async(baz, std::ref(x));  // ����baz(x)

    auto f5 = std::async(move_only());  // ����tmp()��tmp��ͨ��std::move(move_only())����õ�


}

X baz(X &x)
{
    return X();
}
