#pragma once
#include <iostream>

template <class T>
class B1
{
public:
    void SayHi()
    {
        T* pT = static_cast<T*>(this);   // HUH?? 我将在下面解释

        pT->PrintClassName();
    }
protected:
    void PrintClassName() { std::cout << "This is B1" << std::endl; }
};

class D1 : public B1<D1>
{
public:
    // No overridden functions at all
};

class D2 : public B1<D2>
{
protected:
//public:
    void PrintClassName() { std::cout << "This is D2" << std::endl; }
};