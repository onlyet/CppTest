#include <iostream>

using namespace std;

class B
{
public:
    int ib;
public:
    B(int i = 1) :ib(i) {}
    virtual void f() { cout << "B::f()" << endl; }
    virtual void Bf() { cout << "B::Bf()" << endl; }
};

/**
 * @brief 24�ֽ�
 * ���Ƿ�������ʾ�����������vtordisp�ֶΣ������ǡ�
    1. ��������д���������麯����
    2. �����ඨ���˹��캯����������������
*/
class B1 : virtual public B
{
public:
    int ib1;
public:
    B1(int i = 100) :ib1(i) {}
    virtual void f() { cout << "B1::f()" << endl; }
    virtual void f1() { cout << "B1::f1()" << endl; }
    virtual void Bf1() { cout << "B1::Bf1()" << endl; }
};

#if 0
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

int main()
{
    B1 a;
    cout << sizeof(B) << endl;
    cout << "B1�����ڴ��СΪ��" << sizeof(a) << endl;

    cout << "[0]B1::vptr";
    cout << "\t��ַ��" << /*(int*)*/(&a) << endl;

    //������B1::vptr�еĺ���
    for (int i = 0; i < 2; ++i)
    {
        cout << "  [" << i << "]";
        Fun fun1 = (Fun) * ((int*)*(int*)(&a) + i);
        fun1();
        cout << "\t��ַ��\t" << (int*)*((int*)*(int*)(&a) + i) << endl;
    }

    //[1]
    cout << "[1]vbptr ";
    cout << "\t��ַ��" << (int*)(&a) + 1 << endl;  //���ָ��ĵ�ַ
    //��������ָ����Ŀ��ָ������
    for (int i = 0; i < 2; i++)
    {
        cout << "  [" << i << "]";

        cout << *(int*)((int*)*((int*)(&a) + 1) + i);

        cout << endl;
    }


    //[2]
    cout << "[2]B1::ib1=" << *(int*)((int*)(&a) + 2);
    cout << "\t��ַ��" << (int*)(&a) + 2;
    cout << endl;

    //[3]
    cout << "[3]ֵ=" << *(int*)((int*)(&a) + 3);
    cout << "\t\t��ַ��" << (int*)(&a) + 3;
    cout << endl;

    //[4]
    cout << "[4]B::vptr";
    cout << "\t��ַ��" << (int*)(&a) + 4 << endl;

    //���B::vptr�е��麯��
    for (int i = 0; i < 2; ++i)
    {
        cout << "  [" << i << "]";
        Fun fun1 = (Fun) * ((int*)*((int*)(&a) + 4) + i);
        fun1();
        cout << "\t��ַ:\t" << *((int*)*((int*)(&a) + 4) + i) << endl;
    }

    //[5]
    cout << "[5]B::ib=" << *(int*)((int*)(&a) + 5);
    cout << "\t��ַ: " << (int*)(&a) + 5;
    cout << endl;
}
#endif