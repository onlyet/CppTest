#include <iostream>
#include <Windows.h>
#include "common.h"
#include <vector>

using namespace std;

// ����״̬�ص�
typedef void(*OnProgressCallbackForConnectDeviceSuccess)(char* deviceBleMac, char* deviceBleName);
typedef void(*SetCallBackForConnectDeviceSuccess)(OnProgressCallbackForConnectDeviceSuccess onProgressCallbackForConnectDeviceSuccesss);

// �ʼ��ص�
typedef void(*OnProgressCallbackForRealTimePenDatas)(int x, int y, int preasure);
typedef void(*SetCallBackForRealTimePenDatas)(OnProgressCallbackForRealTimePenDatas onProgressCallbackForConnectDeviceSuccesss);

// �����ص�
typedef void(*OnProgressCallbackForKeyEvent)(int key_value);
typedef void(*SetCallBackForKeyEvent)(OnProgressCallbackForKeyEvent onProgressCallbackForKeyEvent);

typedef int(*DG_openPort)(void);
typedef int(*GetDGBleInfo)(char* dgBleName, char* dgBleMac);
typedef int(*GetDGVersion)(char* dgVersion);
typedef int(*SetDGBleName)(char* dgBleName);
typedef int(*ConnectWPDevice)(void);
typedef int(*DG_gotoupdate)(void);
typedef int(*ConnectWPDeviceByMac)(char* macAddr);
typedef int(*DisconnectWPDevice)(char* deviceBleMac, char* deviceBleName);
typedef int(*GetWPDeviceBleInfo)(char* deviceBleMac, char* deviceBleName);
typedef int(*GetWPDeviceName)(char* deviceName);
typedef int(*GetWPDeviceFirmwareVersion)(char* bleVersion, char* mcuVersion);
typedef int(*GetWPDeviceBatteryState)(int& batteryPercentage, int& batteryState);
typedef int(*GetWPDeviceRTC)(int year, int mon, int day, int hour, int min);
typedef int(*SetWPDeviceName)(char* deviceName);
typedef int(*FactoryResetWP)(void);
typedef int(*GetWPDeviceSN)(char* deviceSN);
typedef int(*SwitchWPToRealTimeMode)(void);

SetCallBackForConnectDeviceSuccess  setCallBackForConnectDeviceSuccess;
SetCallBackForRealTimePenDatas      setCallBackForRealTimePenDatas;
SetCallBackForKeyEvent              setCallBackForKeyEvent;
DG_openPort                         dg_openPort;
GetDGBleInfo                        getDGBleInfo;
GetDGVersion                        gtDGVersion;
SetDGBleName                        setDGBleName;
DG_gotoupdate                       dg_gotoupdate;
ConnectWPDevice                     connectWPDevice;
ConnectWPDeviceByMac                connectWPDeviceByMac;
DisconnectWPDevice                  disconnectWPDevice;
GetWPDeviceBleInfo                  getWPDeviceBleInfo;
GetWPDeviceName                     getWPDeviceName;
GetWPDeviceFirmwareVersion          getWPDeviceFirmwareVersion;
GetWPDeviceBatteryState             getWPDeviceBatteryState;
GetWPDeviceRTC                      getWPDeviceRTC;
SetWPDeviceName                     setWPDeviceName;
FactoryResetWP                      factoryResetWP;
GetWPDeviceSN                       getWPDeviceSN;
SwitchWPToRealTimeMode              switchWPToRealTimeMode;

void callbackForConnectDeviceSuccess(char* deviceBleMac, char* deviceBleName)
{
    cout << "A5��д�����ӳɹ�" << endl;

    int ret = switchWPToRealTimeMode();
    if (ret < 0)
    {
        cout << "switchWPToRealTimeMode failed, ret = " << ret << endl;
    }
}

void callbackForRealTimePenDatas(int x, int y, int preasure)
{
}

void callbackForKeyEvent(int key_value)
{
    static int cnt = 1;
    cout << "key event, cnt = " << cnt++ << endl;
}

bool initialize()
{
    HMODULE hDll = LoadLibrary(L"SerialComDLL.dll");
    if (!hDll)
    {
        return false;
    }

    SetCallBackForConnectDeviceSuccess mySetCallBackForConnectDeviceSuccess = (SetCallBackForConnectDeviceSuccess)GetProcAddress(hDll, "SetCallBackForConnectDeviceSuccess");
    mySetCallBackForConnectDeviceSuccess(callbackForConnectDeviceSuccess);   //���ûص�����

    SetCallBackForRealTimePenDatas mySetCallBackForRealTimePenDatas = (SetCallBackForRealTimePenDatas)GetProcAddress(hDll, "SetCallBackForRealTimePenDatas");
    mySetCallBackForRealTimePenDatas(callbackForRealTimePenDatas);   //���ûص�����

    SetCallBackForKeyEvent mySetCallBackForKeyEvent = (SetCallBackForKeyEvent)GetProcAddress(hDll, "SetCallBackForKeyEvent");
    mySetCallBackForKeyEvent(callbackForKeyEvent);   //���ûص�����


    //if (!(setCallBackForConnectDeviceSuccess && setCallBackForRealTimePenDatas && setCallBackForKeyEvent
    //    && dg_openPort && connectWPDevice && connectWPDeviceByMac && disconnectWPDevice && disconnectWPDevice
    //    && getDGBleInfo && getWPDeviceBleInfo && getWPDeviceSN && switchWPToRealTimeMode))
    //{
    //    return false;
    //}

    dg_openPort = (DG_openPort)GetProcAddress(hDll, "dg_openPort");
    if (dg_openPort() < 0)
    {
        return false;
    }

    //// ���ûص�
    //setCallBackForConnectDeviceSuccess(callbackForConnectDeviceSuccess);
    //setCallBackForRealTimePenDatas(callbackForRealTimePenDatas);
    //setCallBackForKeyEvent(callbackForKeyEvent);

    connectWPDeviceByMac = (ConnectWPDeviceByMac)GetProcAddress(hDll, "connectWPDeviceByMac");
    if (!connectWPDeviceByMac)
    {
        return false;
    }
    switchWPToRealTimeMode = (SwitchWPToRealTimeMode)GetProcAddress(hDll, "switchWPToRealTimeMode");
    if (!switchWPToRealTimeMode)
    {
        return false;
    }


    return true;
}

void start()
{
    vector<unsigned char> mac = { 0xF3, 0xC8, 0xED, 0xF6, 0xC0, 0x48 };

    //if (connectWPDeviceByMac("F3C8EDF6C048") < 0)
    if (connectWPDeviceByMac((char*)mac.data()) < 0)
    {
        cout << "connectWPDeviceByMac failed";
    }

}

void A5ButtonClickDemo()
{
    initialize();
    start();

    system("pause");
}