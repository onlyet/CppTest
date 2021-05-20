#include "common.h"
#include<stdio.h>
#include<jni.h>
#include <JniDemo.h>
#include <iostream>
#include <Windows.h>

using namespace std;


//JNIEXPORT jint JNICALL Java_JniDemo_call
//(JNIEnv *, jobject) {
//    //ÊµÏÖ´úÂë
//    int i = 777;
//    return i;
//}

//void debug_jni_dll()
//{
//
//    //Java_JniDemo_filterString(nullptr, jobject(), jstring());
//    cout << i << endl;
//}




void debug_jni_dll()
{
    //Java_JniDemo_filterString(nullptr, jobject(), jstring());
    int i = 1;
    while (1)
    {
        Sleep(1000);
        cout << "i = " << i << endl;
        ++i;
    }

    system("pause");
}