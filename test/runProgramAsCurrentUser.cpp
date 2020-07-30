//#include "common.h"
//#include <Windows.h>
//#include <wtsapi32.h>
//#include <userenv.h>
//#include <tlhelp32.h>
//#include <tchar.h>
//#include <iostream>
//
//#pragma comment(lib, "Wtsapi32.lib")
//#pragma comment(lib, "Userenv.lib")
//
//using namespace std;
//
//BOOL GetCurrentLogonUserToken(HANDLE& hToken)
//{
//    DWORD dwCurSessionId = WTSGetActiveConsoleSessionId();
//    if (TRUE == WTSQueryUserToken(dwCurSessionId, &hToken))
//        return TRUE;
//    DWORD err = GetLastError();
//    BOOL bRet = FALSE;
//    HANDLE hProcessSnap = NULL;
//    PROCESSENTRY32 pe32;
//    DWORD dwSessionId = -1;
//
//    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
//    if (hProcessSnap == INVALID_HANDLE_VALUE)
//    {
//        return FALSE;
//    }
//
//    pe32.dwSize = sizeof(PROCESSENTRY32);
//    if (Process32First(hProcessSnap, &pe32))
//    {
//        do
//        {
//            if (!_tcsicmp(pe32.szExeFile, _T("explorer.exe")))
//            {
//                ::ProcessIdToSessionId(pe32.th32ProcessID, &dwSessionId);
//                if (dwSessionId != dwCurSessionId)
//                    continue;
//                //{
//                HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pe32.th32ProcessID);
//                DWORD err = GetLastError();
//                //bRet = OpenProcessToken(hProcess, TOKEN_ALL_ACCESS, &hToken);
//                bRet = OpenProcessToken(hProcess, TOKEN_READ | TOKEN_QUERY | TOKEN_DUPLICATE | TOKEN_ASSIGN_PRIMARY, &hToken);
//                
//                if (bRet == 0)
//                {
//                }
//
//                CloseHandle(hProcessSnap);
//                return TRUE;
//                //}	 
//            }
//
//        } while (Process32Next(hProcessSnap, &pe32));
//
//        bRet = TRUE;
//    }
//    else
//    {
//        bRet = FALSE;
//    }
//    CloseHandle(hProcessSnap);
//
//    return bRet;
//}
//
//
//void runAsCurUser()
//{
//    //获取当前活动的SessionId
//    DWORD dwSessionId = WTSGetActiveConsoleSessionId();
//    HANDLE hToken = NULL;
//    HANDLE hTokenDup = NULL;
//    LPVOID  pEnv = NULL;
//    STARTUPINFO si;
//    PROCESS_INFORMATION pi;
//
//    HANDLE htoken;
//
//
//    //获取用户Token
//    if (!WTSQueryUserToken(dwSessionId, &hToken))
//    {
//        //cout << "getLastError: " << GetLastError() << endl;
//
//        HANDLE h;
//        if (!GetCurrentLogonUserToken(h))
//        {
//            CloseHandle(hToken);
//            return;
//        }
//        hToken = h;
//
//        //CloseHandle(hToken);
//        //return;
//    }
//
//    //复制Token
//    if (!DuplicateTokenEx(hToken, MAXIMUM_ALLOWED, NULL, SecurityIdentification, TokenPrimary, &hTokenDup))
//    {
//        CloseHandle(hToken);
//        return;
//    }
//
//    //获取环境信息
//    if (!CreateEnvironmentBlock(&pEnv, hTokenDup, FALSE))
//    {
//        CloseHandle(hToken);
//        CloseHandle(hTokenDup);
//        return;
//    }
//
//    //设置启动参数信息
//    ZeroMemory(&si, sizeof(STARTUPINFO));
//    si.cb = sizeof(STARTUPINFO);
//    si.lpDesktop = (WCHAR*)_T("winsta0\\default");
//    ZeroMemory(&pi, sizeof(pi));
//    DWORD dwCreationFlag = NORMAL_PRIORITY_CLASS | CREATE_UNICODE_ENVIRONMENT | CREATE_NEW_CONSOLE;
//
//    //以当前用户启动记事本
//    //if (!CreateProcessAsUser(hTokenDup, _T("C:/Software/Notepad++/notepad++.exe"), NULL, NULL, NULL, FALSE, dwCreationFlag, pEnv, NULL, &si, &pi))
//    //if (!CreateProcessAsUser(hTokenDup, _T("D:/dev/loadDll/Win32/Debug/loadDll.exe"), NULL, NULL, NULL, FALSE, dwCreationFlag, pEnv, NULL, &si, &pi))
//    ////if (!CreateProcessAsUser(hTokenDup, _T("C:/Windows/System32/WindowsPowerShell/v1.0/powershell.exe"), NULL, NULL, NULL, FALSE, dwCreationFlag, pEnv, NULL, &si, &pi))
//    //{
//        //返回2可能是路径不对
//        //cout << "getLastError: " << GetLastError() << endl;
//
//    htoken = hTokenDup;
//        if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &htoken)) 
//        {
//            size_t s = sizeof(TOKEN_PRIVILEGES) + 2 * sizeof(LUID_AND_ATTRIBUTES);
//            TOKEN_PRIVILEGES *p = (PTOKEN_PRIVILEGES)malloc(s);
//            if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &(p->Privileges[0].Luid)) ||
//                !LookupPrivilegeValue(NULL, SE_BACKUP_NAME, &(p->Privileges[1].Luid)) ||
//                !LookupPrivilegeValue(NULL, SE_RESTORE_NAME, &(p->Privileges[2].Luid))) 
//            {
//                cout << "LookupPrivilegeValue failed!" << endl;
//                free(p);
//                return;
//            }
//            p->PrivilegeCount = 3;
//            for (int i = 0; i<3; ++i)
//                p->Privileges[i].Attributes = SE_PRIVILEGE_ENABLED;
//
//            if (!AdjustTokenPrivileges(htoken, FALSE, p, s, NULL, NULL) || GetLastError() != ERROR_SUCCESS)
//            {
//                cout << "AdjustTokenPrivileges failed!" << endl;
//                free(p);
//                return;
//            }
//            //do something here...
//            free(p);
//        }
//        else 
//        {
//            cout << "Open process token failed!" << endl;
//            return;
//        }
//
//        hTokenDup = htoken;
//
//        //if (!CreateProcessAsUser(hTokenDup, _T("D:/dev/loadDll/Win32/Debug/loadDll.exe"), NULL, NULL, NULL, FALSE, dwCreationFlag, pEnv, NULL, &si, &pi))
//        if (!CreateProcessAsUser(hTokenDup, _T("C:/Windows/System32/WindowsPowerShell/v1.0/powershell.exe"), NULL, NULL, NULL, FALSE, dwCreationFlag, pEnv, NULL, &si, &pi))
//        {
//            cout << "getLastError: " << GetLastError() << endl;
//
//            DestroyEnvironmentBlock(pEnv);
//            CloseHandle(hTokenDup);
//            CloseHandle(hToken);
//        }
//    //}
//
//    //等待启动的进程结束
//    WaitForSingleObject(pi.hProcess, INFINITE);
//
//    //清理工作
//    DestroyEnvironmentBlock(pEnv);
//    CloseHandle(hTokenDup);
//    CloseHandle(hToken);
//}
