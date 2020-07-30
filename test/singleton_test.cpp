#include "common.h"


template<typename DerivedClass>
struct Singleton
{
    static DerivedClass& Instance() {
        static DerivedClass m_instance;
        return m_instance;
    }
protected:
    Singleton() = default;
    ~Singleton() = default;
private:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(Singleton&) = delete;
};

class A : public Singleton<A> {
public:
    void Show() { cout << "A::show()" << endl; }
private:
    friend Singleton<A>;
    A() { cout << "A()" << endl; }
    ~A() { cout << "~A()" << endl; }
};
class B {
public:
    void Show() { cout << "B" << endl; }
private:
    friend Singleton<B>;
    B() {}
    ~B() {}
};

void TestSingleton()
{
    //A a;
    A::Instance().Show();
    //Singleton<B>::Instance().Show();
}