#include "common.h"

//#include <Windows.h>  
#include <iostream>  
#include <DXGI.h>  
#include <vector>  
#include <string>
using namespace std;

std::string WStringToString(const std::wstring &wstr)
{
	std::string str(wstr.length(), ' ');
	std::copy(wstr.begin(), wstr.end(), str.begin());
	return str;
}

int getGpuInfo()
{
	// ��������  
	IDXGIFactory * pFactory;
	IDXGIAdapter * pAdapter;
	std::vector <IDXGIAdapter*> vAdapters;            // �Կ�           
	int iAdapterNum = 0; // �Կ�������  

	// ����һ��DXGI����  
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory));

	if (FAILED(hr))
		return -1;

	// ö��������  
	while (pFactory->EnumAdapters(iAdapterNum, &pAdapter) != DXGI_ERROR_NOT_FOUND)
	{
		vAdapters.push_back(pAdapter);
		++iAdapterNum;
	}

	// ��Ϣ���   
	std::cout << "===============��ȡ��" << iAdapterNum << "���Կ�===============" << std::endl;
	for (size_t i = 0; i < vAdapters.size(); i++)
	{
		// ��ȡ��Ϣ  
		DXGI_ADAPTER_DESC adapterDesc;
		vAdapters[i]->GetDesc(&adapterDesc);
		std::wstring aa(adapterDesc.Description);
		std::string bb = WStringToString(aa);
		// ����Կ���Ϣ  
		std::cout << "ϵͳ��Ƶ�ڴ�:" << adapterDesc.DedicatedSystemMemory / 1024 / 1024 << "M" << std::endl;
		std::cout << "ר����Ƶ�ڴ�:" << adapterDesc.DedicatedVideoMemory / 1024 / 1024 << "M" << std::endl;
		std::cout << "����ϵͳ�ڴ�:" << adapterDesc.SharedSystemMemory / 1024 / 1024 << "M" << std::endl;
		std::cout << "�豸����:" << bb.c_str() << std::endl;
	}
	vAdapters.clear();

	system("pause");
}