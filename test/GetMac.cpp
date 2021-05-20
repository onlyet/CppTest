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
            // ȷ��MAC��ַ�ĳ���Ϊ 00-00-00-00-00-00
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
            // ȷ������̫��
            if (pAdapter->Type != MIB_IF_TYPE_ETHERNET)
                continue;
            // ȷ��MAC��ַ�ĳ���Ϊ 00-00-00-00-00-00
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
    // ��ȡ�����ǵ�һ�������ַ
    bool b = GetMacByGetAdaptersAddresses(mac);
    string mac2;
    // ��ȡ����̫�������ַ
    b = GetMacByGetAdaptersInfo(mac2);
}



BOOL getMainBoardByCmd(char *lpszBaseBoard) 
{
    const long MAX_COMMAND_SIZE = 10000; // ��������������С	

    WCHAR szFetCmd[] = L"wmic baseboard get serialnumber";	
    const string strEnSearch = "SerialNumber"; // �������кŵ�ǰ����Ϣ

    BOOL   bret = FALSE;
    HANDLE hReadPipe = NULL; //��ȡ�ܵ�
    HANDLE hWritePipe = NULL; //д��ܵ�	
    PROCESS_INFORMATION pi; //������Ϣ	
    memset(&pi, 0, sizeof(pi));
    STARTUPINFO	si;	//���������д�����Ϣ
    memset(&si, 0, sizeof(si));
    SECURITY_ATTRIBUTES sa; //��ȫ����
    memset(&sa, 0, sizeof(sa));

    char szBuffer[MAX_COMMAND_SIZE + 1] = { 0 }; // ���������н�������������
    string	strBuffer;
    unsigned long count = 0;
    long ipos = 0;

    pi.hProcess = NULL;
    pi.hThread = NULL;
    si.cb = sizeof(STARTUPINFO);
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    //1.�����ܵ�
    bret = CreatePipe(&hReadPipe, &hWritePipe, &sa, 0);
    if (!bret) {
        CloseHandle(hWritePipe);
        CloseHandle(hReadPipe);

        return bret;
    }

    //2.���������д��ڵ���ϢΪָ���Ķ�д�ܵ�
    GetStartupInfo(&si);
    si.hStdError = hWritePipe;
    si.hStdOutput = hWritePipe;
    si.wShowWindow = SW_HIDE; //���������д���
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

    //3.������ȡ�����еĽ���
    bret = CreateProcess(NULL, szFetCmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
    if (!bret) {
        CloseHandle(hWritePipe);
        CloseHandle(hReadPipe);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        return bret;
    }

    //4.��ȡ���ص�����
    WaitForSingleObject(pi.hProcess, 200);
    bret = ReadFile(hReadPipe, szBuffer, MAX_COMMAND_SIZE, &count, 0);
    if (!bret) {
        CloseHandle(hWritePipe);
        CloseHandle(hReadPipe);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        return bret;
    }

    //5.��������ID
    bret = FALSE;
    strBuffer = szBuffer;
    ipos = strBuffer.find(strEnSearch);

    if (ipos < 0) { // û���ҵ�
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

    //ȥ���м�Ŀո� \r \n
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