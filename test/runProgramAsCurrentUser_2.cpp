//#include "common.h"
//#include <Windows.h>
//#include <wtsapi32.h>
//#include <userenv.h>
//#include <tlhelp32.h>
//#include <tchar.h>
//#include <iostream>
//
//using namespace std;
//
//BOOL GetCurrentLogonUserToken__(HANDLE& hToken)
//{
//    DWORD dwCurSessionId = WTSGetActiveConsoleSessionId();
//    if (TRUE == WTSQueryUserToken(dwCurSessionId, &hToken))
//        return TRUE;
//
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
//                bRet = OpenProcessToken(hProcess, TOKEN_ALL_ACCESS, &hToken);
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
//BOOL MyCreateProcessAsUser(const HANDLE& hCurrentToken, LPCTSTR strPath, LPTSTR lpCmdLine)
//{
//    HANDLE hTokenDup = NULL;
//    if (!DuplicateTokenEx(hCurrentToken, MAXIMUM_ALLOWED, NULL, SecurityIdentification,
//        TokenPrimary, &hTokenDup))
//    {
//        cout << "failed" << endl;
//        return FALSE;
//    }
//
//    // 创建一个低权限的SID
//    PSID pIntegritySid = NULL;
//    TOKEN_MANDATORY_LABEL tml;
//    SID_IDENTIFIER_AUTHORITY MLAuthority = SECURITY_MANDATORY_LABEL_AUTHORITY;
//    BOOL bRet = AllocateAndInitializeSid(&MLAuthority, 1, SECURITY_MANDATORY_MEDIUM_RID, 0, 0, 0, 0, 0, 0, 0, &pIntegritySid);
//    tml.Label.Attributes = SE_GROUP_INTEGRITY;
//    tml.Label.Sid = pIntegritySid;
//
//    // 设置这个低权限SID到令牌
//    //bRet = SetTokenInformation(hTokenDup, TokenIntegrityLevel, &tml, (sizeof(tml) + GetLengthSid(pIntegritySid)));
//
//
//    DWORD dwSessionID = WTSGetActiveConsoleSessionId();
//    if (!SetTokenInformation(hTokenDup, TokenSessionId, &dwSessionID, sizeof(DWORD)))
//    {
//        cout << "error: " << GetLastError() << endl;
//        CloseHandle(hTokenDup);
//        return FALSE;
//    }
//
//    STARTUPINFO si;
//    PROCESS_INFORMATION pi;
//    ZeroMemory(&si, sizeof(STARTUPINFO));
//    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
//    si.cb = sizeof(STARTUPINFO);
//    si.lpDesktop = L"WinSta0\\Default";
//    si.dwFlags = STARTF_USESHOWWINDOW;
//    si.wShowWindow = HIDE_WINDOW;
//
//    LPVOID pEnv = NULL;
//    DWORD dwCreationFlags = NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT;
//    if (!CreateEnvironmentBlock(&pEnv, hTokenDup, FALSE))
//    {
//        CloseHandle(hTokenDup);
//        return FALSE;
//    }
//
//    //if (!CreateProcessAsUser(hTokenDup, strPath, lpCmdLine, NULL, NULL, FALSE, dwCreationFlags, pEnv, NULL, &si, &pi))
//    if (!CreateProcessAsUser(hTokenDup, strPath, NULL, NULL, NULL, FALSE, dwCreationFlags, pEnv, NULL, &si, &pi))
//    {
//        cout << "error: " << GetLastError() << endl;
//        CloseHandle(hTokenDup);
//        if (pEnv != NULL)
//            DestroyEnvironmentBlock(pEnv);
//        return FALSE;
//    }
//
//    CloseHandle(pi.hProcess);
//    CloseHandle(pi.hThread);
//    CloseHandle(hTokenDup);
//    if (pEnv != NULL)
//        DestroyEnvironmentBlock(pEnv);
//
//    return TRUE;
//}
//
//void runProgramAsCurrentUser_v2()
//{
//    HANDLE h;
//
//    if (!GetCurrentLogonUserToken__(h))
//    {
//        cout << "failed to get token" << endl;
//        return;
//    }
//
//    MyCreateProcessAsUser(h, _T("C:/Windows/System32/WindowsPowerShell/v1.0/powershell.exe"), NULL);
//
//    cout << "end" << endl;
//}