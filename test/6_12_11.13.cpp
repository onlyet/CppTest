////#include <iostream>
////#include <memory>
////#include <string.h>
////#include <vector>
////
////using namespace std;
////
////class CTest
////{
////public:
////    int n;
////    CTest() :n(5)
////    {
////        cout << "ctor, addr: " << hex << (int)this << endl;
////    }
////    CTest(const CTest& rhs) : 
////        n(rhs.n)
////    {
////        cout << "copy ctor, addr: " << hex << (int)this << endl;
////    }
////    ~CTest()
////    {
////        printf("[%s] [%p]\n", __FUNCTION__, this);
////    }
////};
////CTest func(CTest Temp)
////{
////    printf("[%s]_Temp [%p]\n", __FUNCTION__, &Temp);
////    return Temp;
////}
////int main() {
////    CTest Temp;
////    printf("[%s]_Temp [%p]\n", __FUNCTION__, &Temp);
////    printf("n is [%d]\n", func(Temp).n);
////
////    system("pause");
////}