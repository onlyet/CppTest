#include <iostream>

//���Զ�λ�������ڴ�й¶ ���ڵ��ļ��;�����һ�У����ڼ�� malloc ������ڴ�
#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h>
#include <crtdbg.h>

//�ѷ����ڴ����Ϣ�������������Զ�λ����һ�з������ڴ�й¶�����ڼ�� new ������ڴ�
#ifdef _DEBUG
#define new   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

//����
inline void EnableMemLeakCheck()
{
    //������ڳ����˳�ʱ�Զ����� _CrtDumpMemoryLeaks(),���ڶ���˳����ڵ����.
    //���ֻ��һ���˳�λ�ã������ڳ����˳�֮ǰ���� _CrtDumpMemoryLeaks()
    _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
}


void memory_leak_demo()
{
    EnableMemLeakCheck();

    //���е� �� 191 �� �ڴ�����ʱ��ͣ����
    //_CrtSetBreakAlloc(191);

    char* p = new char[100];
    //char* p1 = new char[200];
    //char* p2 = (char*)malloc(600);
    //delete p;

    //getchar();

    //_CrtDumpMemoryLeaks();//�����������������������ڴ������Ϣ
}

