#pragma once
#include <iostream>

class Widget;

class Object
{
public:
    void tt();

protected:
    void protected_func() { std::cout << "Object::protected_func" << std::endl; }
    int protected_data;
};

class Widget : public Object
{
public:
    void call_base_protected_func() {
        protected_func(); 
        protected_data;
    }

    void test();

protected:
    void protected_func() {}
};