// 不能将this指针作为shared_ptr返回，否则会出现两个智能指针各自有一个引用计数，出现两次析构

#if 0
#include <iostream>
#include <memory>
using namespace std;
class A
{
public:
    shared_ptr<A> GetSelf()
    {
        return shared_ptr<A>(this); // 不要这么做
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