#if 0

#include "CSystemStatus.h"
#include <Shlwapi.h>
#include <windows.h>
#include <string>
#include <Iphlpapi.h>
#include <tchar.h>

#pragma comment(lib,"Iphlpapi.lib") 
#pragma comment(lib, "Pdh.lib")
#pragma comment(lib, "Shlwapi.lib")
 
 
CSystemStatus::CSystemStatus()
{
	m_Query = NULL;
	m_CpuTotal = NULL;
	m_DiskRead = NULL;
	m_DiskWrite= NULL;
	m_NetDownload=NULL;
	m_NetUpload=NULL;
	//SystemInit();
}
 
CSystemStatus::~CSystemStatus()
{
	if (m_CpuTotal){
		PdhRemoveCounter(m_CpuTotal);
		m_CpuTotal = NULL;
	}
	if (m_CpuTotal){
		PdhRemoveCounter(m_CpuTotal);
		m_CpuTotal = NULL;
	}
	if (m_DiskRead){
		PdhRemoveCounter(m_DiskRead);
		m_DiskRead = NULL;
	}
	if (m_DiskWrite){
		PdhRemoveCounter(m_DiskWrite);
		m_DiskWrite = NULL;
	}
	if (m_NetDownload)
	{	
		PdhRemoveCounter(m_NetDownload);
		m_NetDownload = NULL;
	}
	if (m_NetUpload)
	{
		PdhRemoveCounter(m_NetUpload);
		m_NetUpload = NULL;
	}
	if(m_Query){
		PdhCloseQuery(m_Query);
		m_Query = NULL;
	}
	//SystemUnInit();
}
 

//��ʼ��
void CSystemStatus::SystemInit(DWORD object)
{
	PDH_STATUS state;
	state = PdhOpenQuery(NULL, NULL, &m_Query);

	if (object&SYSSTATE_CPU_USAGE)	//CPUʹ����
		state = PdhAddCounter(m_Query, _T("\\Processor(_Total)\\% Processor Time"), NULL, &m_CpuTotal);
	if (object&SYSSTATE_DISK_READ)	//���̶��ٶ�
		state = PdhAddCounter(m_Query, _T("\\PhysicalDisk(_Total)\\Disk Read Bytes/sec"), NULL, &m_DiskRead);
	if (object&SYSSTATE_DISK_WRITE)	//����д�ٶ�
		state = PdhAddCounter(m_Query, _T("\\PhysicalDisk(_Total)\\Disk Write Bytes/sec"), NULL, &m_DiskWrite);
	if (object&SYSSTATE_NET_DOWNLOAD)//���������ٶ�
		state = PdhAddCounter(m_Query, _T("\\Network Interface(killer E2200 Gigabit Ethernet Controller)\\Bytes Received/sec"), NULL, &m_NetDownload);
	if (object&SYSSTATE_NET_UPLOAD)	//�����ϴ��ٶ�
		state = PdhAddCounter(m_Query, _T("\\Network Interface(killer E2200 Gigabit Ethernet Controller)\\Bytes Sent/sec"), NULL, &m_NetUpload);

	state = PdhCollectQueryData(m_Query);
	Sleep(500);             //����Ҫ����ʱ��Ȼ����൱��׼ȷ  
	state =	PdhCollectQueryData(m_Query); 
}

//��ȡ���������ٶȣ�K/s��
double CSystemStatus::GetSystemNetDownloadRate()
{
	PDH_FMT_COUNTERVALUE counterVal;
	PDH_STATUS lStatus = PdhGetFormattedCounterValue(m_NetDownload, PDH_FMT_DOUBLE, NULL, &counterVal);
	if(ERROR_SUCCESS != lStatus)  return -1;
	double dbVal= counterVal.doubleValue; 
	double NetDownload = (double)((dbVal/(1024*1.0f)));
	return NetDownload;
}

//��ȡ�����ϴ��ٶ�
double CSystemStatus::GetSystemNetUploadRate()
{
	PDH_FMT_COUNTERVALUE counterVal;
	PDH_STATUS lStatus = PdhGetFormattedCounterValue(m_NetUpload, PDH_FMT_DOUBLE, NULL, &counterVal);
	if(ERROR_SUCCESS != lStatus)  return -1;
	double dbVal= counterVal.doubleValue; 
	double NetUpload = (double)((dbVal/(1024*1.0f)));
	return NetUpload;
}

//��ȡϵͳ��ǰ���̶�����(K/s)
double CSystemStatus::GetSystemDiskReadRate()
{
	PDH_FMT_COUNTERVALUE counterVal;
	PDH_STATUS lStatus = PdhGetFormattedCounterValue(m_DiskRead, PDH_FMT_DOUBLE, NULL, &counterVal);
	if(ERROR_SUCCESS != lStatus)  return -1;
	double dbVal= counterVal.doubleValue; 
	double dbDiskRead = (double)((dbVal/(1024*1.0f)));
	return dbDiskRead;
}

//��ȡϵͳ��ǰ����д����
double CSystemStatus::GetSystemDiskWriteRate()
{
	PDH_FMT_COUNTERVALUE counterVal;
	PDH_STATUS lStatus = PdhGetFormattedCounterValue(m_DiskWrite, PDH_FMT_DOUBLE, NULL, &counterVal);
	if(ERROR_SUCCESS != lStatus)  return -1;
	double dbVal= counterVal.doubleValue; 
	double dbDiskWrite = (double)((dbVal/(1024*1.0f)));
	return dbDiskWrite;
}

//��ȡCPUʹ��ֵ
double CSystemStatus::GetSystemCpuCurrentUsage()
{
	PDH_FMT_COUNTERVALUE counterVal;
	 // CPUʱ�䣬ע��������PDH_FMT_NOCAP100������������CPU��������
	PDH_STATUS lStatus = PdhGetFormattedCounterValue(m_CpuTotal, PDH_FMT_DOUBLE| PDH_FMT_NOCAP100, NULL, &counterVal);
	if(ERROR_SUCCESS != lStatus)  return -1;
	return counterVal.doubleValue;//PDH_INVALID_ARGUMENT PDH_INVALID_DATA 
}
 
//����ʼ��
void CSystemStatus::SystemUnInit()
{
	if (m_CpuTotal){
		PdhRemoveCounter(m_CpuTotal);
		m_CpuTotal = NULL;
	}
	if (m_DiskRead){
		PdhRemoveCounter(m_DiskRead);
		m_DiskRead = NULL;
	}
	if (m_DiskWrite){
		PdhRemoveCounter(m_DiskWrite);
		m_DiskWrite = NULL;
	}
	if (m_NetDownload)
	{	
		PdhRemoveCounter(m_NetDownload);
		m_NetDownload = NULL;
	}
	if (m_NetUpload)
	{
		PdhRemoveCounter(m_NetUpload);
		m_NetUpload = NULL;
	}
	if(m_Query){
		PdhCloseQuery(m_Query);
		m_Query = NULL;
	}
}

#if 0
// ��ȡϵͳ����Ӳ��ʹ�����		
void CSystemStatus::GetSystemDiskStatus(ULONGLONG& AllDiskTotal, ULONGLONG& AllDiskFree)
{
	int DType = 0;
	int si = 0;
	BOOL bResult = FALSE;
	int DiskCount = 0;
	ULONGLONG nTempTotal = 0;
	ULONGLONG nTempFree = 0;

	ULONGLONG i64FreeBytesToCaller;  
	ULONGLONG i64TotalBytes;  
	ULONGLONG i64FreeBytes;

	//ö�ٴ�������
	DWORD DiskInfo = GetLogicalDrives();
	while (DiskInfo){
		if (DiskInfo & 1){
			++DiskCount;
		}
		DiskInfo = DiskInfo >> 1;
	}
	int test = DiskCount;
	int DSLength = GetLogicalDriveStrings(0, NULL);

	TCHAR* DStr = NULL;
	while (!DStr){
		DStr = new TCHAR[DSLength];
	}
	if (NULL == DStr){
		return;
	}
	int nRet = GetLogicalDriveStrings(DSLength, (LPTSTR)DStr);

	//ö�ٴ�������
	for (int i = 0;i < DSLength / 4; i++){
		TCHAR strDisk[3] = {0};
		_stprintf(strDisk, _T("%c:"), DStr[si]);
		DType = GetDriveType(DStr + i * 4);
		bResult = GetDiskFreeSpaceEx(
			strDisk, 
			(PULARGE_INTEGER)&i64FreeBytesToCaller,
			(PULARGE_INTEGER)&i64TotalBytes,
			(PULARGE_INTEGER)&i64FreeBytes);

		if (bResult){
			nTempTotal += (ULONGLONG)i64TotalBytes / 1024 / 1024 / 1024;
			nTempFree += (ULONGLONG)i64FreeBytesToCaller / 1024 / 1024 / 1024;
		}
		else{
			OutputDebugString(_T("�豸δ׼��..."));
		}
		si += 4;
	}
	AllDiskTotal = nTempTotal;
	AllDiskFree = nTempFree;

	delete[] DStr;
}

// ��ȡϵͳ����Ӳ��ʹ�����		
void CSystemStatus::GetSystemDiskStatus(std::vector<EACHDISKSTATUS> &vectorDisk)
{
	int DType = 0;
	int si = 0;
	BOOL bResult = FALSE;
	int DiskCount = 0;
	ULONGLONG nTempTotal = 0;
	ULONGLONG nTempFree = 0;

	ULONGLONG i64FreeBytesToCaller;  
	ULONGLONG i64TotalBytes;  
	ULONGLONG i64FreeBytes;

	//ö�ٴ�������
	DWORD DiskInfo = GetLogicalDrives();
	while (DiskInfo){
		if (DiskInfo & 1){
			++DiskCount;
		}
		DiskInfo = DiskInfo >> 1;
	}
	int test = DiskCount;
	int DSLength = GetLogicalDriveStrings(0, NULL);

	TCHAR* DStr = NULL;
	while (!DStr){
		DStr = new TCHAR[DSLength];
	}
	if (NULL == DStr){
		return;
	}
	int nRet = GetLogicalDriveStrings(DSLength, (LPTSTR)DStr);

	EACHDISKSTATUS diskstatus;
	//ö�ٴ�������
	for (int i = 0;i < DSLength / 4; i++){
		TCHAR strDisk[3] = {0};
		_stprintf(strDisk, _T("%c:"), DStr[si]);
		DType = GetDriveType(DStr + i * 4);
		bResult = GetDiskFreeSpaceEx(
			strDisk, 
			(PULARGE_INTEGER)&i64FreeBytesToCaller,
			(PULARGE_INTEGER)&i64TotalBytes,
			(PULARGE_INTEGER)&i64FreeBytes);

		if (bResult)
		{
			diskstatus._strdir=strDisk[0];
			double total = ((i64TotalBytes  / 1024 / 1024)  * 100)/ 1024;
			diskstatus._Total=total/100.0f;
			double OfFree = ((i64FreeBytesToCaller  / 1024 / 1024)  * 100)/ 1024;
			diskstatus._OfFree=OfFree/100.0f;
			vectorDisk.push_back(diskstatus);
		}
		else
		{
			OutputDebugString(_T("�豸δ׼��..."));
		}
		si += 4;
	}

	delete[] DStr;
}

//��ȡϵͳ��ǰ����״̬
void CSystemStatus::GetSystemCurrentDiskStatus(ULONGLONG& TatolMB, ULONGLONG& FreeCaller)
{
	BOOL bResult = FALSE;
	ULONGLONG nTempTotal = 0;
	ULONGLONG nTempFree = 0;

	ULONGLONG ui64FreeBytesToCaller;  
	ULONGLONG ui64TotalBytes;  
	ULONGLONG ui64FreeBytes;

	TCHAR szModule[MAX_PATH*2] = {0};
	GetModuleFileName(NULL, szModule, MAX_PATH*2);
#ifdef _UNICODE
	wstring strPath(szModule);
	wstring strDirve = strPath.substr(0, 1);
#else
	std::string strPath(szModule);
	std::string strDirve = strPath.substr(0, 1);
#endif
	TCHAR szDisk[3] = {0};
	_stprintf(szDisk, _T("%c:"), strDirve[0]);
	bResult = GetDiskFreeSpaceEx(
		szDisk, 
		(PULARGE_INTEGER)&ui64FreeBytesToCaller,	//�û����õĴ��̿ռ�
		(PULARGE_INTEGER)&ui64TotalBytes,			//�����ܹ��Ŀռ�
		(PULARGE_INTEGER)&ui64FreeBytes);			//���̿��еĿռ�.���϶����ֽ�Ϊ��λ��
	if (bResult){
		nTempTotal = ui64TotalBytes / 1024 / 1024 / 1024;
		nTempFree = ui64FreeBytesToCaller / 1024 / 1024 / 1024;
		TatolMB = nTempTotal;
		FreeCaller = nTempFree;
	}
}

//��ȡϵͳ��ǰ����ʹ����
double CSystemStatus::GetSystemCurrentDiskUsage()
{
	BOOL bResult = FALSE;
	ULONGLONG ui64FreeBytesToCaller;  
	ULONGLONG ui64TotalBytes;  
	ULONGLONG ui64FreeBytes;

	TCHAR szModule[MAX_PATH*2] = {0};
	GetModuleFileName(NULL, szModule, MAX_PATH*2);
	::PathRemoveFileSpec(szModule);
#ifdef _UNICODE
	wstring strPath(szModule);
	wstring strDirve = strPath.substr(0, 1);
#else
	std::string strPath(szModule);
	std::string strDirve = strPath.substr(0, 1);
#endif

	TCHAR szDisk[3] = {0};
	_stprintf(szDisk, _T("%c:"), strDirve[0]);
	bResult = GetDiskFreeSpaceEx(
		szDisk, 
		(PULARGE_INTEGER)&ui64FreeBytesToCaller,	//�û����õĴ��̿ռ�
		(PULARGE_INTEGER)&ui64TotalBytes,			//�����ܹ��Ŀռ�
		(PULARGE_INTEGER)&ui64FreeBytes);			//���̿��еĿռ�.���϶����ֽ�Ϊ��λ��
	if (bResult){
		double TempNum  = ((ui64TotalBytes / 1024 / 1024 / 1024)-(ui64FreeBytesToCaller/ 1024 / 1024 / 1024))* 100.0 / (ui64TotalBytes/ 1024 / 1024 / 1024);
		return TempNum;
	}
	return 0;
}

#endif
 
//�����ڴ��ʹ��
BOOL CSystemStatus::GetPhysicalMemoryState(ULONGLONG& totalPhysMem, ULONGLONG& physMemUsed)
{
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	totalPhysMem = memInfo.ullTotalPhys;
	physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
	return TRUE;
}
 
//���������ڴ�����(�ܿ����ڴ�)
double CSystemStatus::GetTotalPhysicalMemory()
{
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	double totalPhysMem = ((memInfo.ullTotalPhys  / 1024 / 1024)  * 100)/ 1024;
	double fTemptotal = totalPhysMem / 100.0;
	return fTemptotal;
}

//���������ڴ�����(�����ڴ�)
double CSystemStatus::GetTotalPhysicalMemoryFree()
{
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	double physMemFree = (((memInfo.ullAvailPhys) / 1024 / 1024) * 100) / 1024;;
	double fTemMemFree = physMemFree / 100.0;
	return fTemMemFree;
}
 
//���������ڴ�ʹ��(��ʹ���ڴ�)
double CSystemStatus::GetTotalPhysicalMemoryUsed()
{
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	double physMemUsed = (((memInfo.ullTotalPhys - memInfo.ullAvailPhys) / 1024 / 1024) * 100) / 1024;;
	double fTemMemUsed = physMemUsed / 100.0;
	return fTemMemUsed;
}
 
//���������ڴ�ʹ���� 
double CSystemStatus::GetPhysicalMemoryUsage()
{
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	double MemUsage = memInfo.dwMemoryLoad;
	return MemUsage;
}

//��ȡ������Ϣ���ڻ�ȡ����ʱ��Ҫ�õ�����������
void CSystemStatus::GetNetCardInfo(std::vector<NETCARDINFO> &vectorNetCard)
{

	NETCARDINFO NetCardInfo;

	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
	//�õ��ṹ���С,����GetAdaptersInfo����
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);
	//����GetAdaptersInfo����,���pIpAdapterInfoָ�����;����stSize��������һ��������Ҳ��һ�������
	int nRel = GetAdaptersInfo(pIpAdapterInfo,&stSize);
	//��¼��������
	int netCardNum = 0;
	//��¼ÿ�������ϵ�IP��ַ����
	int IPnumPerNetCard = 0;
	if (ERROR_BUFFER_OVERFLOW == nRel)
	{
		//����������ص���ERROR_BUFFER_OVERFLOW
		//��˵��GetAdaptersInfo�������ݵ��ڴ�ռ䲻��,ͬʱ�䴫��stSize,��ʾ��Ҫ�Ŀռ��С
		//��Ҳ��˵��ΪʲôstSize����һ��������Ҳ��һ�������
		//�ͷ�ԭ�����ڴ�ռ�
		delete pIpAdapterInfo;
		//���������ڴ�ռ������洢����������Ϣ
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
		//�ٴε���GetAdaptersInfo����,���pIpAdapterInfoָ�����
		nRel=GetAdaptersInfo(pIpAdapterInfo,&stSize);    
	}
	if (ERROR_SUCCESS == nRel)
	{
		//���������Ϣ
		//�����ж�����,���ͨ��ѭ��ȥ�ж�
		while (pIpAdapterInfo)
		{
			++netCardNum;				//��������

			NetCardInfo.Name=pIpAdapterInfo->AdapterName;		//��������
			NetCardInfo.Description=pIpAdapterInfo->Description;//��������
			
			switch(pIpAdapterInfo->Type)//��������
			{
			case MIB_IF_TYPE_OTHER:break;
			case MIB_IF_TYPE_ETHERNET:break;
			case MIB_IF_TYPE_TOKENRING:break;
			case MIB_IF_TYPE_FDDI:break;
			case MIB_IF_TYPE_PPP:break;
			case MIB_IF_TYPE_LOOPBACK:break;
			case MIB_IF_TYPE_SLIP:break;
			}
			//����MAC��ַ
			char tempchar[4];
			for (DWORD i = 0; i < pIpAdapterInfo->AddressLength; i++)
				if (i < pIpAdapterInfo->AddressLength-1)
				{
					printf("%02X-", pIpAdapterInfo->Address[i]);
		
					sprintf(tempchar,"%02X-",pIpAdapterInfo->Address[i]);
					NetCardInfo.Local_Mac+=tempchar;
					

				}
				else
				{
					printf("%02X", pIpAdapterInfo->Address[i]);
		
					sprintf(tempchar,"%02X",pIpAdapterInfo->Address[i]);
					NetCardInfo.Local_Mac+=tempchar;
					
				}
			
			//����IP��ַ
			//���������ж�IP,���ͨ��ѭ��ȥ�ж�
			IP_ADDR_STRING *pIpAddrString =&(pIpAdapterInfo->IpAddressList);
			do 
			{
				//cout<<"�������ϵ�IP������"<<++IPnumPerNetCard<<endl;
				//cout<<"IP ��ַ��"<<pIpAddrString->IpAddress.String<<endl;
				//cout<<"������ַ��"<<pIpAddrString->IpMask.String<<endl;
				//cout<<"���ص�ַ��"<<pIpAdapterInfo->GatewayList.IpAddress.String<<endl;

				NetCardInfo.Local_IP=pIpAddrString->IpAddress.String;

				pIpAddrString=pIpAddrString->Next;
			} while (pIpAddrString);

			vectorNetCard.push_back(NetCardInfo);

			pIpAdapterInfo = pIpAdapterInfo->Next;
		}

	}
	if (pIpAdapterInfo)
	{
		delete pIpAdapterInfo;

		pIpAdapterInfo=NULL;
	}
}

//��ȡ����ϵͳ��Ϣ 
void CSystemStatus::GetOsInfo(std::string &osinfo)
{
	// get os name according to version number
	SYSTEM_INFO system_info;
	memset(&system_info,0,sizeof(SYSTEM_INFO));
	GetSystemInfo(&system_info);

	OSVERSIONINFOEX  osver = { sizeof(OSVERSIONINFO) };
	osver.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
	GetVersionEx((OSVERSIONINFO*)&osver);
	std::string os_name;
	if (osver.dwMajorVersion == 4 && osver.dwMinorVersion == 0)
	{
		if(osver.dwPlatformId==VER_PLATFORM_WIN32_NT) 
			os_name="Microsoft Windows NT 4.0 ";             
		else if(osver.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS) 
			os_name="Microsoft Windows 95 "; 
	}
	else if (osver.dwMajorVersion == 4 && osver.dwMinorVersion == 10)
		os_name = "Microsoft Windows 98";
	else if (osver.dwMajorVersion == 4 && osver.dwMinorVersion == 90)
		os_name = "Microsoft Windows Me";
	else if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 0)
	{
		os_name = "Microsoft Windows 2000";
		if(osver.wSuiteMask==VER_SUITE_ENTERPRISE) 
			os_name+=" Advanced Server "; 
	}
	else if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 1)
	{
		os_name = "Microsoft Windows XP";

		if(osver.wSuiteMask==VER_SUITE_EMBEDDEDNT) 
			os_name+=" Embedded "; 
		else if(osver.wSuiteMask==VER_SUITE_PERSONAL) 
			os_name+=" Home Edition "; 
		else
			os_name+=" Professional ";
	}
	else if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 2)
	{
		//os_name = "Microsoft Windows vista";
		if(osver.wProductType==VER_NT_WORKSTATION &&system_info.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64)
			os_name="Microsoft Windows XP Professional x64 Edition "; 
		if(GetSystemMetrics(SM_SERVERR2)==0 && osver.wSuiteMask==VER_SUITE_BLADE)
			os_name ="Microsoft Windows Server 2003 Web Edition "; 
		else if(GetSystemMetrics(SM_SERVERR2)==0 && osver.wSuiteMask==VER_SUITE_COMPUTE_SERVER) 
			os_name="Microsoft Windows Server 2003 Compute Cluster Edition "; 
		else if(GetSystemMetrics(SM_SERVERR2)==0 &&  osver.wSuiteMask==VER_SUITE_STORAGE_SERVER) 
			os_name="Microsoft Windows Server 2003 Storage Server "; 
		else if(GetSystemMetrics(SM_SERVERR2)==0 &&   osver.wSuiteMask==VER_SUITE_DATACENTER) 
			os_name="Microsoft Windows Server 2003 Datacenter Edition "; 
		else if(GetSystemMetrics(SM_SERVERR2)==0 &&   osver.wSuiteMask==VER_SUITE_ENTERPRISE) 
			os_name="Microsoft Windows Server 2003 Enterprise Edition "; 
		else if(GetSystemMetrics(SM_SERVERR2)!=0 &&   osver.wSuiteMask==VER_SUITE_STORAGE_SERVER)
			os_name="Microsoft Windows Server 2003 R2 Storage Server ";
	}
	else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 0)
	{
		//os_name = "Microsoft Windows 2003";

		if(osver.wProductType==VER_NT_WORKSTATION)
		{
			os_name="Microsoft Windows Vista "; 
			if (osver.wSuiteMask==VER_SUITE_PERSONAL)
				os_name+=" Home";
		}				
		else if(osver.wProductType!=VER_NT_WORKSTATION)
		{
			os_name="Microsoft Windows Server 2008 ";
			if ( osver.wSuiteMask==VER_SUITE_DATACENTER)
				os_name+=" Datacenter Server ";
			else if (osver.wSuiteMask==VER_SUITE_ENTERPRISE)
				os_name+=" Enterprise ";
		}
	}
	else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 1)
	{
		os_name = "Microsoft Windows 7.0";
		/*if(osver.wProductType==VER_NT_WORKSTATION) 
		os_name="Microsoft Windows 7 "; 
		else
		os_name="Microsoft Windows Server 2008 R2 ";*/ 
	}
	else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 2)
	{
		os_name = "Microsoft Windows 8.0";
		/*if (osver.wProductType == VER_NT_WORKSTATION)
		os_name = "Microsoft Windows 8";
		else
		os_name = "Microsoft Windows Server 2012";*/
	}
	else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 3)
	{
		os_name = "Microsoft Windows 8.1";
		/*if (osver.wProductType == VER_NT_WORKSTATION)
		os_name = "Microsoft Windows 8.1";
		else
		os_name = "Microsoft Windows Server 2012 R2";*/
	}
	else if (osver.dwMajorVersion == 10 && osver.dwMinorVersion == 0)
	{
		os_name = "Microsoft Windows 10.0";
		/*	if (osver.wProductType == VER_NT_WORKSTATION)
		os_name = "Microsoft Windows 10.0";
		else
		os_name = "Microsoft Windows Server 2016";*/
	}

	SYSTEM_INFO si;
	GetNativeSystemInfo(&si);
	if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ||  
		si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64 )
		os_name+=" X64";   
	else os_name+= " x86";

	osinfo=os_name;
}

//��ȡCPUӲ����Ϣ 
//void CSystemStatus::GetCpuInfo(std::string &CPUinfo)
//{
//	int cpuInfo[4] = {-1};
//	char cpu_manufacture[32] = { 0 };
//	char cpu_type[32] = { 0 };
//	char cpu_freq[32] = { 0 };
//
//	__cpuid(cpuInfo, 0x80000002);
//	memcpy(cpu_manufacture, cpuInfo, sizeof(cpuInfo));
//
//	__cpuid(cpuInfo, 0x80000003);
//	memcpy(cpu_type, cpuInfo, sizeof(cpuInfo));
//
//	__cpuid(cpuInfo, 0x80000004);
//	memcpy(cpu_freq, cpuInfo, sizeof(cpuInfo));
//
//	std::string manufacture=cpu_manufacture;//������
//	std::string type=cpu_type;				//�ͺ�
//	std::string freq=cpu_freq;				//Ƶ��
//	CPUinfo=manufacture+type+freq;
//}

//��ȡCPUid
//void CSystemStatus::GetCPUid(std::string &CPUid)
//{
//	unsigned long s1,s2,s3,s4; 
//	__asm 
//	{ 
//		mov eax,00h 
//			xor edx,edx 
//			cpuid 
//			mov s1, edx 
//			mov s2, eax 
//	} 
//	__asm 
//	{ 
//		mov eax,01h 
//			xor ecx,ecx 
//			xor edx,edx 
//			cpuid 
//			mov s3, edx 
//			mov s4, ecx 
//	} 
//
//	CString st;
//	st.Format("%08X%08X%08X%08X",s1,s2,s3,s4);
//	CPUid=st.GetBuffer(0);
//	st.ReleaseBuffer();
//}



//BOOL CSystemStatus::GetHDSerial(std::string &HDSerial)
//{ 
//	BOOL		bRtn     = FALSE;
//	DWORD		bytesRtn = 0;
//	char		szhd[80] = {0}; 
//	PIDSECTOR	phdinfo; 
//	HANDLE		hDrive	 = NULL; 
//	GETVERSIONOUTPARAMS vers; 
//	SENDCMDINPARAMS		in; 
//	SENDCMDOUTPARAMS	out; 
//
//	ZeroMemory(&vers, sizeof(vers)); 
//	ZeroMemory(&in  , sizeof(in)); 
//	ZeroMemory(&out , sizeof(out)); 
//
//	//�����ĸ�����Ӳ�̣�ȡ��һ�������ݵ�����Ӳ�� 
//	for (int j=0; j<4; j++)
//	{
//		sprintf(szhd,	"\\\\.\\PhysicalDrive%d",j); 
//		hDrive = CreateFileA(szhd, 
//			GENERIC_READ|GENERIC_WRITE, 
//			FILE_SHARE_READ|FILE_SHARE_WRITE,
//			0,
//			OPEN_EXISTING,
//			0,
//			0); 
//		if (NULL == hDrive)continue; 
//		
//		if (!DeviceIoControl(hDrive, DFP_GET_VERSION, 0, 0, &vers, sizeof(vers), &bytesRtn,0))goto FOREND;
//		//If IDE identify command not supported, fails 
//		if (!(vers.fCapabilities&1))goto FOREND;
//
//		//Identify the IDE drives 
//		if (j&1)in.irDriveRegs.bDriveHeadReg = 0xb0; 
//		else in.irDriveRegs.bDriveHeadReg = 0xa0; 
//		 
//		if (vers.fCapabilities&(16>>j))goto FOREND;	//We don't detect a ATAPI device. 
//		else in.irDriveRegs.bCommandReg = 0xec; 
//		 
//		in.bDriveNumber = j; 
//		in.irDriveRegs.bSectorCountReg  = 1; 
//		in.irDriveRegs.bSectorNumberReg = 1; 
//		in.cBufferSize = 512; 
//
//		if (!DeviceIoControl(hDrive, DFP_RECEIVE_DRIVE_DATA, &in, sizeof(in), &out, sizeof(out), &bytesRtn,0))
//		{ 
//			//"DeviceIoControl failed:DFP_RECEIVE_DRIVE_DATA"<<endl; 
//			goto FOREND; 			
//		} 
//		phdinfo=(PIDSECTOR)out.bBuffer; 
//
//		char	s[21] = {0};		
//		memcpy(s, phdinfo->sSerialNumber, 20); 		
//		s[20] = 0; 
//		ChangeByteOrder(s, 20); 
//
//		//ɾ���ո��ַ�
//		int ix = 0;
//		for (ix=0; ix<20; ix++)
//		{
//			if (s[ix] == ' ')continue;
//			break;
//		}
//		char lpszHD[128]={0};
//		memcpy(lpszHD, s+ix, 20);
//
//		HDSerial=lpszHD;
//
//		bRtn = TRUE;
//		if (bRtn)break;				
//FOREND:
//		CloseHandle(hDrive); 
//		hDrive = NULL; 
//	}
//
//	CloseHandle(hDrive); 
//	hDrive = NULL; 
//	return(bRtn);
//}

#include <stdio.h>

int main()

{
    CSystemStatus getCpuUseage;

    while (true)

    {
        getCpuUseage.SystemInit();
        printf("CPUʹ���ʣ�%0.2f\n", getCpuUseage.GetSystemCpuCurrentUsage());

        //Sleep(1000);

    }

    return 0;

}

#endif