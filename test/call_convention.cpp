//#include "common.h"
//
///**
//* 打印结果：
//* &x= 00A7F688
//* &y= 00A7F68C
//* &z= 00A7F690
//* 可以判断在VST015的编译器，栈底是高地址，栈顶是低地址
//*/
//int _cdecl func_param_pass_seq(int x, int y, int z)
//{
//    cout << "&x= " << &x << endl;
//    cout << "&y= " << &y << endl;
//    cout << "&z= " << &z << endl;
//
//
//    return x + y + z;
//}
//
//void func_param_pass_seq_()
//{
//    func_param_pass_seq(1, 2, 3);
//}
//
//
//void __cdecl __cdecl_callee(int a, int b)
//{
//	cout << "__cdecl, a = " << a << ", b = " << b << endl;
//}
//
//void __stdcall __stdcall_callee(int a, int b)
//{
//	cout << "__stdcall, a = " << a << ", b = " << b << endl;
//}
//
//void __cdecl_caller()
//{
//    const char *t = "abcdefg\n";
//    int n = 3;
//    __asm
//    {
//        push y
//        push x
//        call __cdecl_callee
//		pop x
//		pop y
//    }
//}
//
//void __stdcall_caller()
//{
//	int x = 1;
//	int y = 2;
//	__asm
//	{
//		push y
//		push x
//		call __stdcall_callee
//
//	}
//}
//
//void __cdecl_caller_v2()
//{
//    unsigned long dwEsp;
//    const char *t = "abcdefg\n";
//    int n = 3;
//    __asm
//    {
//        mov dwEsp, esp
//        push n
//        push t
//        call cdecl_asm_test
//        push y
//        push x
//        call __cdecl_callee
//        mov esp, dwEsp
//    }
//}
//
//
////int __stdcall disassembly_demo(int x, int y, int z)
////{
////    return x + y + z;
////}   
////void disassembly_demo_()
////{
////    disassembly_demo(1, 2, 3);
////}
//
//
//int __cdecl __cdecl_disassembly_callee(int a, int b)
//{
//    const char *t = "abcdefg\n";
//    int n = 3;
//    __asm
//    {
//        push n
//        push t
//        call cdecl_asm_test
//        pop n
//        pop t
//    }
//}
//
//int __stdcall __stdcall_disassembly_callee(int a, int b)
//{
//	return a + b;
//}
//
//void __cdecl_disassembly_caller()
//{
//	__cdecl_disassembly_callee(1, 2);
//}
//
//void __stdcall_disassembly_caller()
//{
//	__stdcall_disassembly_callee(1, 2);
//}