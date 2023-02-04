#include "common.h"

#include <winsock2.h>
#include <iphlpapi.h>
#include <windows.h>

#include <string>

#pragma comment(lib, "IPHLPAPI.lib")

bool GetMacByGetAdaptersAddresses(std::string& macOUT)
{
    bool ret = false;

    ULONG outBufLen = sizeof(IP_ADAPTER_ADDRESSES);
    PIP_ADAPTER_ADDRESSES pAddresses = (IP_ADAPTER_ADDRESSES*)malloc(outBufLen);
    if (pAddresses == NULL)
        return false;
    // Make an initial call to GetAdaptersAddresses to get the necessary size into the ulOutBufLen variable
    if (GetAdaptersAddresses(AF_UNSPEC, 0, NULL, pAddresses, &outBufLen) == ERROR_BUFFER_OVERFLOW)
    {
        free(pAddresses);
        pAddresses = (IP_ADAPTER_ADDRESSES*)malloc(outBufLen);
        if (pAddresses == NULL)
            return false;
    }

    if (GetAdaptersAddresses(AF_UNSPEC, 0, NULL, pAddresses, &outBufLen) == NO_ERROR)
    {
        // If successful, output some information from the data we received
        for (PIP_ADAPTER_ADDRESSES pCurrAddresses = pAddresses; pCurrAddresses != NULL; pCurrAddresses = pCurrAddresses->Next)
        {
            // 确保MAC地址的长度为 00-00-00-00-00-00
            if (pCurrAddresses->PhysicalAddressLength != 6)
                continue;
            char acMAC[32];
   /*         sprintf(acMAC, "%02X-%02X-%02X-%02X-%02X-%02X",
                int(pCurrAddresses->PhysicalAddress[0]),
                int(pCurrAddresses->PhysicalAddress[1]),
                int(pCurrAddresses->PhysicalAddress[2]),
                int(pCurrAddresses->PhysicalAddress[3]),
                int(pCurrAddresses->PhysicalAddress[4]),
                int(pCurrAddresses->PhysicalAddress[5]));*/
            sprintf_s(acMAC, "%02X-%02X-%02X-%02X-%02X-%02X",
                int(pCurrAddresses->PhysicalAddress[0]),
                int(pCurrAddresses->PhysicalAddress[1]),
                int(pCurrAddresses->PhysicalAddress[2]),
                int(pCurrAddresses->PhysicalAddress[3]),
                int(pCurrAddresses->PhysicalAddress[4]),
                int(pCurrAddresses->PhysicalAddress[5]));
            macOUT = acMAC;
            ret = true;
            break;
        }
    }

    free(pAddresses);
    return ret;
}



bool GetMacByGetAdaptersInfo(std::string& macOUT)
{
    bool ret = false;

    ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
    PIP_ADAPTER_INFO pAdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
    if (pAdapterInfo == NULL)
        return false;
    // Make an initial call to GetAdaptersInfo to get the necessary size into the ulOutBufLen variable
    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
    {
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO *)malloc(ulOutBufLen);
        if (pAdapterInfo == NULL)
            return false;
    }

    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == NO_ERROR)
    {
        for (PIP_ADAPTER_INFO pAdapter = pAdapterInfo; pAdapter != NULL; pAdapter = pAdapter->Next)
        {
            // 确保是以太网
            if (pAdapter->Type != MIB_IF_TYPE_ETHERNET)
                continue;
            // 确保MAC地址的长度为 00-00-00-00-00-00
            if (pAdapter->AddressLength != 6)
                continue;
            char acMAC[32];
            sprintf_s(acMAC, "%02X-%02X-%02X-%02X-%02X-%02X",
                int(pAdapter->Address[0]),
                int(pAdapter->Address[1]),
                int(pAdapter->Address[2]),
                int(pAdapter->Address[3]),
                int(pAdapter->Address[4]),
                int(pAdapter->Address[5]));
            macOUT = acMAC;
            ret = true;
            break;
        }
    }

    free(pAdapterInfo);
    return ret;
}


void getMacAddress()
{
    string mac;
    // 获取到的是第一个物理地址
    bool b = GetMacByGetAdaptersAddresses(mac);
    string mac2;
    // 获取到以太网物理地址
    b = GetMacByGetAdaptersInfo(mac2);
}



BOOL getMainBoardByCmd(char *lpszBaseBoard) 
{
    const long MAX_COMMAND_SIZE = 10000; // 命令行输出缓冲大小	

    WCHAR szFetCmd[] = L"wmic baseboard get serialnumber";	
    const string strEnSearch = "SerialNumber"; // 主板序列号的前导信息

    BOOL   bret = FALSE;
    HANDLE hReadPipe = NULL; //读取管道
    HANDLE hWritePipe = NULL; //写入管道	
    PROCESS_INFORMATION pi; //进程信息	
    memset(&pi, 0, sizeof(pi));
    STARTUPINFO	si;	//控制命令行窗口信息
    memset(&si, 0, sizeof(si));
    SECURITY_ATTRIBUTES sa; //安全属性
    memset(&sa, 0, sizeof(sa));

    char szBuffer[MAX_COMMAND_SIZE + 1] = { 0 }; // 放置命令行结果的输出缓冲区
    string	strBuffer;
    unsigned long count = 0;
    long ipos = 0;

    pi.hProcess = NULL;
    pi.hThread = NULL;
    si.cb = sizeof(STARTUPINFO);
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    //1.创建管道
    bret = CreatePipe(&hReadPipe, &hWritePipe, &sa, 0);
    if (!bret) {
        CloseHandle(hWritePipe);
        CloseHandle(hReadPipe);

        return bret;
    }

    //2.设置命令行窗口的信息为指定的读写管道
    GetStartupInfo(&si);
    si.hStdError = hWritePipe;
    si.hStdOutput = hWritePipe;
    si.wShowWindow = SW_HIDE; //隐藏命令行窗口
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

    //3.创建获取命令行的进程
    bret = CreateProcess(NULL, szFetCmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
    if (!bret) {
        CloseHandle(hWritePipe);
        CloseHandle(hReadPipe);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        return bret;
    }

    //4.读取返回的数据
    WaitForSingleObject(pi.hProcess, 200);
    bret = ReadFile(hReadPipe, szBuffer, MAX_COMMAND_SIZE, &count, 0);
    if (!bret) {
        CloseHandle(hWritePipe);
        CloseHandle(hReadPipe);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        return bret;
    }

    //5.查找主板ID
    bret = FALSE;
    strBuffer = szBuffer;
    ipos = strBuffer.find(strEnSearch);

    if (ipos < 0) { // 没有找到
        CloseHandle(hWritePipe);
        CloseHandle(hReadPipe);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        return bret;
    }
    else {
        strBuffer = strBuffer.substr(ipos + strEnSearch.length());
    }

    memset(szBuffer, 0x00, sizeof(szBuffer));
    strcpy_s(szBuffer, strBuffer.c_str());

    //去掉中间的空格 \r \n
    int j = 0;
    for (int i = 0; i < strlen(szBuffer); i++) {
        if (szBuffer[i] != ' ' && szBuffer[i] != '\n' && szBuffer[i] != '\r') {
            lpszBaseBoard[j] = szBuffer[i];
            j++;
        }
    }

    CloseHandle(hWritePipe);
    CloseHandle(hReadPipe);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return TRUE;
}



void getMainboardId()
{
    char id[1024] = { 0 };
    bool b = getMainBoardByCmd(id);
}