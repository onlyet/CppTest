// ���ܽ�thisָ����Ϊshared_ptr���أ�����������������ָ�������һ�����ü�����������������

#if 0
#include <iostream>
#include <memory>
using namespace std;
class A
{
public:
    shared_ptr<A> GetSelf()
    {
        return shared_ptr<A>(this); // ��Ҫ��ô��
    }
    A()
    {
        cout << "A()" << endl;
    }
    ~A()
    {
        cout << "Deconstruction A" << endl;
    }
};
int main()
{
    shared_ptr<A> sp1(new A);
    shared_ptr<A> sp2 = sp1->GetSelf();
    cout << "sp1 use_count:" << sp1.use_count() << endl;
    cout << "sp2 use_count:" << sp2.use_count() << endl;
    
    return 0;
}

#elif 0
#include <iostream>
#include <memory>
using namespace std;
class A : public std::enable_shared_from_this<A>
{
public:
    shared_ptr<A>GetSelf()
    {
        return shared_from_this();
    }
    A()
    {
        cout << "A()" << endl;
    }
    ~A()
    {
        cout << "Deconstruction A" << endl;
    }
};
int main()
{
    shared_ptr<A> sp1(new A);
    shared_ptr<A> sp2 = sp1->GetSelf(); // ok
    cout << "sp1 use_count:" << sp1.use_count() << endl;
    cout << "sp2 use_count:" << sp2.use_count() << endl;
    return 0;
}
#endif