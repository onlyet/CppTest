#pragma once
#include <iostream>

using namespace std;

class Base
{
public:
    Base() { cout << "Base()" << endl; }
    Base(const Base&) { cout << "Base(const Base&)" << endl; }
    ~Base() { cout << "~Base()" << endl; }
};

class Derive : public Base
{
public:
    Derive() { cout << "Derive()" << endl; }
    Derive(const Derive&) { cout << "Derive(const Derive&)" << endl; }
    ~Derive() { cout << "~Derive()" << endl; } 
};

void derive_test();