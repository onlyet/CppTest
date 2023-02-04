#pragma once

#include <string>
#include <future>
struct X
{
    void foo(int, std::string const&);
    std::string bar(std::string const&);
};

struct Y
{
    Y();
    Y(const Y&);
    Y(Y&&);
    double operator()(double);
};

class move_only
{
public:
    move_only();
    move_only(move_only&&);
    move_only(move_only const&) = delete;
    move_only& operator=(move_only&&);
    move_only& operator=(move_only const&) = delete;

    void operator()();
};

X baz(X&);
