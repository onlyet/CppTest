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
	// 参数定义  
	IDXGIFactory * pFactory;
	IDXGIAdapter * pAdapter;
	std::vector <IDXGIAdapter*> vAdapters;            // 显卡           
	int iAdapterNum = 0; // 显卡的数量  

	// 创建一个DXGI工厂  
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory));

	if (FAILED(hr))
		return -1;

	// 枚举适配器  
	while (pFactory->EnumAdapters(iAdapterNum, &pAdapter) != DXGI_ERROR_NOT_FOUND)
	{
		vAdapters.push_back(pAdapter);
		++iAdapterNum;
	}

	// 信息输出   
	std::cout << "===============获取到" << iAdapterNum << "块显卡===============" << std::endl;
	for (size_t i = 0; i < vAdapters.size(); i++)
	{
		// 获取信息  
		DXGI_ADAPTER_DESC adapterDesc;
		vAdapters[i]->GetDesc(&adapterDesc);
		std::wstring aa(adapterDesc.Description);
		std::string bb = WStringToString(aa);
		// 输出显卡信息  
		std::cout << "系统视频内存:" << adapterDesc.DedicatedSystemMemory / 1024 / 1024 << "M" << std::endl;
		std::cout << "专用视频内存:" << adapterDesc.DedicatedVideoMemory / 1024 / 1024 << "M" << std::endl;
		std::cout << "共享系统内存:" << adapterDesc.SharedSystemMemory / 1024 / 1024 << "M" << std::endl;
		std::cout << "设备描述:" << bb.c_str() << std::endl;
	}
	vAdapters.clear();

	system("pause");
}