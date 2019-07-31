#include "common.h"

/**
* 打印结果：
* &x= 00A7F688
* &y= 00A7F68C
* &z= 00A7F690
* 可以判断在VST015的编译器，栈底是高地址，栈顶是低地址
*/
int _cdecl func_param_pass_seq(int x, int y, int z)
{
    cout << "&x= " << &x << endl;
    cout << "&y= " << &y << endl;
    cout << "&z= " << &z << endl;


    return x + y + z;
}

void func_param_pass_seq_()
{
    func_param_pass_seq(1, 2, 3);
}


static void cdecl_asm_test(char *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << a;
    }
}

//void cdecl_asm_test_()
//{
//    char *t = "abcdefg\n";
//    int n = 3;
//    __asm
//    {
//        push n
//        push t
//        call cdecl_asm_test
//    }
//}

void cdecl_asm_test_()
{
    const char *t = "abcdefg\n";
    int n = 3;
    __asm
    {
        push n
        push t
        call cdecl_asm_test
        pop t
        pop n
    }
}

void asm_test_()
{
    unsigned long dwEsp;
    const char *t = "abcdefg\n";
    int n = 3;
    __asm
    {
        mov dwEsp, esp
        push n
        push t
        call cdecl_asm_test
        mov esp, dwEsp
    }
}

void asm_test2_()
{
    const char *t = "abcdefg\n";
    int n = 3;
    __asm
    {
        push n
        push t
        call cdecl_asm_test
        pop n
        pop t
    }
}


int __stdcall disassembly_demo(int x, int y, int z)
{
    return x + y + z;
}   

void disassembly_demo_()
{
    disassembly_demo(1, 2, 3);
}