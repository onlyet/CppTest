#include <typeinfo>
#include <iostream>

using namespace std;

class Person {
public:
    virtual ~Person() {}
};

class Employee : public Person { };

//int main()
//{
//    Person person;
//    Employee employee;
//    Person* ptr = &employee;
//    Person& ref = employee;
//
//    std::cout << typeid(int).name() << std::endl;
//    std::cout << typeid(Employee).name() << std::endl;
//    std::cout << typeid(*ptr).name() << std::endl;
//    std::cout << typeid(ptr).name() << std::endl;
//    std::cout << typeid(ref).name() << std::endl;
//
//    const type_info& ti = typeid(ref);
//    cout << ti.hash_code() << endl;
//
//    return 0;
//}