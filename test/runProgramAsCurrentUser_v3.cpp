#include "common.h"
#include <Windows.h>
#include <wtsapi32.h>
#include <userenv.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <iostream>

using namespace std;

void runAsUser()
{
    SID_IDENTIFIER_AUTHORITY MLAuthority = SECURITY_MANDATORY_LABEL_AUTHORITY;
    PSID pIntegritySid = NULL;
    TOKEN_MANDATORY_LABEL tml;
    DWORD dwCreationFlag;
    LPVOID pEnvironment;

    HANDLE hToken = NULL;
    HANDLE hNewToken = NULL;

    STARTUPINFO Si = { 0 };
    PROCESS_INFORMATION Pi = { 0 };

    Si.cb = sizeof(Si);
    Si.lpDesktop = TEXT("winsta0\\default");
    Si.wShowWindow = SW_SHOW;

    dwCreationFlag = NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT;

    BOOL bRet = OpenProcessToken(GetCurrentProcess(), TOKEN_DUPLICATE | TOKEN_QUERY | TOKEN_ADJUST_DEFAULT | TOKEN_ASSIGN_PRIMARY, &hToken);

    bRet = DuplicateTokenEx(hToken, 0, NULL, SecurityImpersonation, TokenPrimary, &hNewToken);

    // 创建一个低权限的SID
    bRet = AllocateAndInitializeSid(&MLAuthority, 1, SECURITY_MANDATORY_MEDIUM_RID, 0, 0, 0, 0, 0, 0, 0, &pIntegritySid);

    tml.Label.Attributes = SE_GROUP_INTEGRITY;
    tml.Label.Sid = pIntegritySid;

    // 设置这个低权限SID到令牌
    bRet = SetTokenInformation(hNewToken, TokenIntegrityLevel, &tml, (sizeof(tml) + GetLengthSid(pIntegritySid)));

    // 创建一个环境变量
    bRet = CreateEnvironmentBlock(&pEnvironment, hToken, FALSE);

    // 创建一个低权限的进程
    //bRet = CreateProcessAsUser(hNewToken, TEXT("C:/Windows/System32/WindowsPowerShell/v1.0/powershell.exe"),
    //    NULL, NULL, NULL, FALSE, dwCreationFlag, pEnvironment, NULL, &Si, &Pi);

    bRet = CreateProcessAsUser(hNewToken, TEXT("D:/dev/loadDll/Win32/Debug/loadDll.exe"),
        NULL, NULL, NULL, FALSE, dwCreationFlag, pEnvironment, NULL, &Si, &Pi);
}

