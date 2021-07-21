//#include "common.h"

//#if 1
//int main()
//{
//    test();
//    system("pause");
//    return 0;
//}
//#endif


#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void GetMemory(char* p)
{
    p = (char*)malloc(100);
}
int main()
{
    //char* str = NULL;
    const char* str = "HELLO";
    //GetMemory(str);
    //strcpy(str, "hello world");
    printf("str:%s\n", str);
    printf(str);
    return 0;
}