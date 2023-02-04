#include "common.h"
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <tchar.h>
#include <iostream>

using namespace std;

#pragma comment(lib,"Ole32.lib")
#pragma comment(lib,"OleAut32.lib")

bool EnumAllOfficeFilePath()
{
	CLSID clsid;
	CoInitialize(NULL);
	HRESULT hr = S_FALSE;

	IRunningObjectTable* pRot = NULL;
	IEnumMoniker* pEnumMoniker = NULL;
	IMoniker* pMoniker = NULL;
	hr = GetRunningObjectTable(0, &pRot);
	if (FAILED(hr))
	{
		cout << "GetRunningObjectTable failed" << endl;
		return false;
	}

	hr = pRot->EnumRunning(&pEnumMoniker);
	if (FAILED(hr))
	{
		cout << "EnumRunning failed" << endl;
		return false;
	}

	hr = pEnumMoniker->Reset();
	if (FAILED(hr))
	{
		cout << "Reset failed" << endl;
		return false;
	}

	IBindCtx *pbc;
	CreateBindCtx(0, &pbc);
	int index = 1;

	while ((hr = pEnumMoniker->Next(1, &pMoniker, NULL)) == S_OK)
	{
		OLECHAR* szDisplayName;
		hr = pMoniker->GetDisplayName(pbc, NULL, &szDisplayName);
		if (FAILED(hr))
		{
			cout << "GetDisplayName failed" << endl;
		}
		else
		{
			DWORD dwLen = WideCharToMultiByte(CP_ACP, 0, szDisplayName, -1, NULL, 0, NULL, FALSE);
			char* szResult = new char[dwLen];
			WideCharToMultiByte(CP_ACP, 0, szDisplayName, -1, szResult, dwLen, NULL, FALSE);
			printf("%d:%s\n", index++, szResult);
			delete[] szResult;

		}

		pMoniker->Release();
	}

	pbc->Release();
	pEnumMoniker->Release();
	pRot->Release();

	CoUninitialize();
	return true;
}


//int main(int argc, char* argv[])
//{
//	EnumAllOfficeFilePath();
//	return 0;
//}