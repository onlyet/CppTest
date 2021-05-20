#include "common.h"

#include <iostream>
#include <list>

std::ostream& operator<<(std::ostream& ostr, const std::list<int>& list)
{
    for (auto &i : list) {
        ostr << " " << i;
    }
    return ostr;
}

void list_demo()
{
    std::list<int> list1 = { 1, 2, 3, 4, 5 };
    std::list<int> list2 = { 10, 20, 30, 40, 50 };

    auto it = list1.begin();
    std::advance(it, 2);

    cout << *it << endl;
    list1.splice(it, list2);

    std::cout << "list1: " << list1 << "\n";
    std::cout << "list2: " << list2 << "\n";

    cout << *it << endl;
    list2.splice(list2.begin(), list1, it, list1.end());
    cout << *it << endl;

    std::cout << "list1: " << list1 << "\n";
    std::cout << "list2: " << list2 << "\n";
}