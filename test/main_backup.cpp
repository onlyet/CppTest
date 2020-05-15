#include "common.h"


#include<iostream>
#include<string>
#include<map>
#include<unordered_set>
#include<assert.h>
#include <memory>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <set>
#include <mutex>
//#include <zlib.h>


using namespace std;

//int main()
//{
//	string str("hello");
//	//string str2("world");
//	//map<string, string> m;
//	//m.insert(pair<string,string>(str, str2));
//	//cout << str << endl;
//	//cout << m[str] << endl;
//
//	std::string&& str2 = std::move(str);
//	std::string copy = std::move(str);
//	//cout << str2 << endl;
//	cout << str << endl;
//	string str3 = str;
//	cout << str3 << endl;
//
//	system("pause");
//	return 0;
//}

static bool ValidateSensorType(unsigned int sensor_type)
{
    bool ret = false;
    std::unordered_set<unsigned int> types{ 7, 9 , 10 ,11, 13, 15, 16, 20, 21, 22,
        28, 30, 31, 32, 34, 37, 39, 44, 45, 46,
        47, 48, 49, 51, 52, 53, 520 };

    auto it = types.find(sensor_type);
    if (it != types.end())
    {
        ret = true;
    }

    return ret;
}

//int main()
//{
//	if (ValidateSensorType(520)) {
//		cout << "sensor can be controled" << endl;
//	}
//	else {
//		cout << "can not find" << endl;
//	}
//
//	system("pause");
//	return 0;
//}

//void test()
//{
//    //char a[2][3] = { "ab", "cd" };
//    char a[2][3] = { {'a','b'},{'c','d'} };
//    //char *p = a[0];
//    char *p = *a;
//    int i = 2;
//    while (i > 0) {
//        cout << p << " ";
//        p = *(a + 1);
//        --i;
//    }
//}

//int main()
//{
//	test();
//	system("pause");
//	return 0;
//}

#include <chrono>
#include <ratio>

using namespace std::chrono;

class Timer {
public:
    using s = std::ratio<1, 1>;
    using ms = std::ratio<1, 1000>;
    using us = std::ratio<1, 1000000>;
    using ns = std::ratio<1, 1000000000>;
public:
    Timer() : tpStart(high_resolution_clock::now()), tpStop(tpStart) {}
public:
    void start() { tpStart = high_resolution_clock::now(); }
    void stop() { tpStop = high_resolution_clock::now(); }
    template <typename span>
    auto delta() const { return duration<double, span>(high_resolution_clock::now() - tpStart).count(); }
    template <typename span>
    auto stop_delta() { stop(); return duration<double, span>(tpStop - tpStart).count(); }
    template <typename span>
    auto stop_delta_start() {
        stop();
        auto ts = duration<double, span>(tpStop - tpStart).count();
        start();
        return ts;
    }
private:
    time_point<high_resolution_clock> tpStart;
    time_point<high_resolution_clock> tpStop;
};

//int main()
//{
//	int cnt = 0;
//	Timer t;
//	for (int i = 0; i < 1000000; ++i) {
//		++cnt;
//	}
//	cout << "time duration is " << t.stop_delta<Timer::s>() << endl;
//
//	system("pause");
//	return 0;
//}

//#include <sstream>
//#include <string.h>
//using namespace std;
//
//int main() {
//
//	int number = 33;
//	//stringstream strs;
//	//strs << number;
//	//string temp_str = strs.str();
//	//char* char_type = (char*)temp_str.c_str();
//
//	//cout << temp_str << " " << temp_str.size() << endl;
//	//cout << char_type << endl;
//
//	string str_send_msg;
//	int len_send = 8;
//	int command_send = 4;
//
//	cout << sizeof(int) << endl;
//	//str_send_msg.append((char*)&len_send, sizeof(len_send));
//	//str_send_msg.append((char*)&command_send, sizeof(command_send));
//	char buf[1024] = { 0 };
//	memcpy_s(buf, sizeof(int), (char*)&len_send, sizeof(int));
//	memcpy_s(buf + sizeof(int), sizeof(int), (char*)&command_send, sizeof(int));
//	//cout << buf << endl;
//	str_send_msg.append(buf, 8);
//
//
//	cout << str_send_msg << " " << str_send_msg.size() << endl;
//
//	/*std::string s = std::to_string(number);
//	cout << s << " " << s.size() << endl;*/
//
//	system("pause");
//	return 0;
//}


//#include <stdio.h>
//#include <conio.h>
//#include <Windows.h>
//#include <tchar.h>
//#include <iostream>
//#include <winerror.h>
//
//using namespace std;
//
//#pragma comment(lib,"Ole32.lib")
//#pragma comment(lib,"OleAut32.lib")
//
//bool EnumAllOfficeFilePath()
//{
//	CLSID clsid;
//	CoInitialize(NULL);
//	HRESULT hr = S_FALSE;
//
//	IRunningObjectTable* pRot = NULL;
//	IEnumMoniker* pEnumMoniker = NULL;
//	IMoniker* pMoniker = NULL;
//	hr = GetRunningObjectTable(0, &pRot);
//	if (FAILED(hr))
//	{
//		cout << "GetRunningObjectTable failed" << endl;
//		return false;
//	}
//	hr = pRot->EnumRunning(&pEnumMoniker);
//	if (FAILED(hr))
//	{
//		cout << "EnumRunning failed" << endl;
//		return false;
//	}
//
//	hr = pEnumMoniker->Reset();
//	if (FAILED(hr))
//	{
//		cout << "Reset failed" << endl;
//		return false;
//	}
//
//	IBindCtx *pbc;
//	CreateBindCtx(0, &pbc);
//	int index = 1;
//
//	while ((hr = pEnumMoniker->Next(1, &pMoniker, NULL)) == S_OK)
//	{
//		OLECHAR* szDisplayName;
//		hr = pMoniker->GetDisplayName(pbc, NULL, &szDisplayName);
//		if (FAILED(hr))
//		{
//			cout << "GetDisplayName failed" << endl;
//		}
//		else
//		{
//			DWORD dwLen = WideCharToMultiByte(CP_ACP, 0, szDisplayName, -1, NULL, 0, NULL, FALSE);
//			char* szResult = new char[dwLen];
//			WideCharToMultiByte(CP_ACP, 0, szDisplayName, -1, szResult, dwLen, NULL, FALSE);
//			printf("%d:%s\n", index++, szResult);
//
//
//
//			delete[] szResult;
//
//		}
//
//		pMoniker->Release();
//	}
//
//	pbc->Release();
//	pEnumMoniker->Release();
//	pRot->Release();
//
//	CoUninitialize();
//	return true;
//}


//int main(int argc, char* argv[])
//{
//	EnumAllOfficeFilePath();
//	system("pause");
//	return 0;
//}


//void GetActiveWordFilePath()
//{
//	CLSID clsid;
//	//初始化OLE
//	CoInitialize(NULL);
//	HRESULT hr = S_FALSE;
//	OLECHAR FAR* szDocMember;
//	OLECHAR FAR* szMember;
//	bool bSucceeded = false;
//	//获取WORD对象的CLASSID
//	hr = CLSIDFromProgID(L"Word.Application", &clsid);
//	szDocMember = L"ActiveDocument";
//
//	if (FAILED(hr))
//	{
//		CoUninitialize();
//		return;
//	}
//
//	IUnknown *pUnk;
//	//获取当前活动对象
//	hr = GetActiveObject(clsid, NULL, (IUnknown**)&pUnk);
//	if (SUCCEEDED(hr))
//	{
//		IDispatch* pDisp;
//		hr = pUnk->QueryInterface(IID_IDispatch, (void**)&pDisp);
//		if (SUCCEEDED(hr))
//		{
//			DISPID dispid;
//			DISPPARAMS dispparamsNoArgs = { NULL, NULL, 0, 0 };
//			VARIANT varResult;
//
//			hr = pDisp->GetIDsOfNames(IID_NULL, &szDocMember, 1, LOCALE_USER_DEFAULT, &dispid);
//			if (SUCCEEDED(hr))
//			{
//				//获取ActiveDocument属性值
//				hr = pDisp->Invoke(dispid, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dispparamsNoArgs, &varResult, NULL, NULL);
//				if (SUCCEEDED(hr))
//				{
//					IDispatch* pDoc = varResult.pdispVal;
//					szMember = L"FullName";
//					hr = pDoc->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_USER_DEFAULT, &dispid);
//					if (SUCCEEDED(hr))
//					{
//						//获取文件路径属性值
//						hr = pDoc->Invoke(dispid, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dispparamsNoArgs, &varResult, NULL, NULL);
//						if (SUCCEEDED(hr))
//						{
//							wchar_t* wbstr = varResult.bstrVal;
//							DWORD dwLen = WideCharToMultiByte(CP_ACP, 0, wbstr, -1, NULL, 0, NULL, FALSE);
//							char* szResult = new char[dwLen];
//							WideCharToMultiByte(CP_ACP, 0, wbstr, -1, szResult, dwLen, NULL, FALSE);
//							cout << "当前打开的WORD文档路径: " << szResult << endl;
//							delete[] szResult;
//						}
//					}
//
//					if (pDoc != NULL)
//						pDoc->Release();
//				}
//
//			}
//
//			if (pDisp != NULL)
//				pDisp->Release();
//		}
//
//		if (pUnk != NULL)
//			pUnk->Release();
//	}
//
//	CoUninitialize();
//
//}
//
//
//int main(int argc, char* argv[])
//{
//	GetActiveWordFilePath();
//	system("pause");
//	return 0;
//}


//int main()
//{
//	//int a[1] = { 0 };
//	//a[10] = 3;
//	//cout << a[10] << endl;
//
//	//int *p = nullptr;
//	//*p = 2;
//
//	string s = "hello";
//	cout << sizeof(s) << endl << s.size() << endl;
//
//	system("pause");
//	return 0;
//}


#define WIN32
#define _CONSOLE

#ifdef WIN32  
#include <io.h>
#include <direct.h>  
#endif  
#ifdef linux   
#include <unistd.h> 
#include <sys/types.h>  
#include <sys/stat.h> 
#endif  
#include <string>

static bool check_dir(const char* dir)
{
    if (_access(dir, 0) == -1)
    {
#ifdef WIN32  
        int flag = _mkdir(dir);
#endif  
#ifdef linux   
        int flag = mkdir(dir.c_str(), 0777);
#endif  
        return (flag == 0);
    }
    return true;
};

#include<assert.h>
void initPath(const char *path)
{
    assert(path != NULL);

    char *head, *p;
    char tmpDir[1024] = { 0 };
    strcpy_s(tmpDir, path);
    head = tmpDir;
    if (*head == '\\' || *head == '/')
        ++head;
    p = head;
    if (*(tmpDir + strlen(path) - 1) != '\\' && *(tmpDir + strlen(path) - 1) != '/')
        *(tmpDir + strlen(path)) = '\\';

    while (*p)
    {
        if (*p == '\\' || *p == '/')
        {
            *p = '\0';
            if (_access(head, 0))// 头文件io.h
            {
                if (_mkdir(head))
                {
#ifdef _DEBUG
                    fprintf(stderr, "Failed to create directory %s\n", head);
#endif
                }
            }
            *p = '\\';
        }
        ++p;
    }
}

//int main()
//{
//	//bool access = check_dir("D:\\aaa\\bbb");
//	//initPath("D:\\aaa\\bbb\\ccc");
//	//initPath("ttt");
//	//initPath("\\ttt\\");
//	//initPath("/dumps/");
//	initPath("/qqq/www/eee/rrr");
//	initPath("/aaa\\www/eee\\rrr");
//	cout << "1" << endl;
//
//	system("pause");
//	return 0;
//}

//int main()
//{
//
//
//	struct tm tm_;
//	auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
//	localtime_s(&tm_, &now);
//	auto tt = std::put_time(&tm_, "%Y_%m_%d_%H_%M_%S");
//	stringstream ss;
//	ss << tt;
//	cout << ss.str() << endl;
//
//	system("pause");
//	return 0;
//}


//int main()
//{
//	list<int> s = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//
//	auto it = s.begin();
//	while (it != s.end())	//原来在这
//	{
//		auto ch = *it;
//		++it;
//		//s.remove(2);	//it失效
//		//s.remove(3);
//		s.remove(9);
//		//s.erase(ch);
//		cout << ch << endl;
//	}
//
//	//while (it != s.end())	
//	//{
//	//	cout << *it << endl;
//	//	auto ch = it;
//	//	++it;
//	//	s.erase(ch);
//	//	it = ch;	//失效的迭代器不能与s.end()比较，崩溃：set/map iteraters not compatible
//	//}
//
//	system("pause");
//	return 0;
//}

//int main()
//{
//	mutex mtx;
//	lock_guard<mutex> lk(mtx);
//	lock_guard<mutex> lk2(mtx);
//
//	system("pause");
//	return 0;
//}

//int main()
//{
//	int a = 5 % 0;
//	system("pause");
//	return 0;
//}

//#include <algorithm>
//int main()
//{
//	vector<int> v = { 1, 3, 5 };
//	v.erase(std::remove(v.begin(), v.end(), 5));
//	for (auto &e : v)
//		cout << e << " "; 
//
//	system("pause");
//	return 0;
//}

bool MakeSureDirExist(const char *dir, size_t len)
{
    assert(dir != NULL);
    if (len < 1 || len > 1024)
        return false;
    char *head, *p;
    char tmpDir[1024] = { 0 };
    //strcpy_s(tmpDir, 1024, dir);	//拷贝1024字节发现，len之后的字符全部变为-2
    strcpy_s(tmpDir, len + 1, dir);
    head = tmpDir;
    if (*head == '\\' || *head == '/')
        ++head;
    p = head;
    if (*(tmpDir + len - 1) != '\\' && *(tmpDir + len - 1) != '/')
        *(tmpDir + len) = '\\';

    while (*p)
    {
        if (*p == '\\' || *p == '/')
        {
            *p = '\0';
            if (_access(head, 0))// 头文件io.h
            {
                if (_mkdir(head))
                {
#ifdef _DEBUG
                    fprintf(stderr, "Failed to create directory %s\n", head);
                    return false;
#endif
                }
            }
            *p = '\\';
        }
        ++p;
    }
    return true;
}


//#include<memory>
//#include<assert.h>
//int main()
//{
//	//int port = 50003;
//	//short s = port;
//	//cout << s << endl;
//
//	//std::unique_ptr<int> p = std::make_unique<int>(2);
//	//p.reset();
//	//assert(p);
//	//unique_ptr<string> p = make_unique<string>("hello");
//	
//	
//	const char *dir = "logs";
//	//bool flag = MakeSureDirExist("logs", 4);
//
//	cout << strlen(dir) << endl;
//	cout << string(dir).size() << endl;
//	cout << strlen(string(dir).c_str()) << endl;
//
//	system("pause");
//	return 0;
//}


struct Foo {};

//int main()
//{
//	/*std::weak_ptr<Foo> wp;
//	cout << wp.expired() << endl;
//	cout << (wp.lock() == nullptr) << endl;*/
//
//	std::list<int> v = { 1,2,3,4,5 };
//	std::list<int>::iterator it = --v.end();
//
//	//v.erase(v.end());
//	v.erase(it);
//	v.erase(it);
//	
//
//	for (auto &e : v)
//		cout << e << " ";
//	cout << endl;
//	system("pause");
//	return 0;
//}

//int main()
//{
//	mutex m;
//	//unique_lock<mutex> lk(m, defer_lock);
//	//lk.lock();
//	//cout << "1" << endl;
//	//lk.unlock();
//
//	while (1)
//	{
//		if (1)
//		{
//			cout << "1" << endl;
//			//lock_guard<mutex> lk(m);
//			unique_lock<mutex> lk(m);
//			{
//				if (1)
//					break;
//			}
//			cout << "2" << endl;
//		}
//		cout << "3" << endl;
//	}
//	cout << "4" << endl;
//
//	system("pause");
//	return 0;
//}

//int main()
//{
//    int err;
//    Byte compr[200], uncompr[200];    // big enough
//    uLong comprLen, uncomprLen;
//    const char* hello = "12345678901234567890123456789012345678901234567890";
//    uLong len = strlen(hello) + 1;
//    comprLen = sizeof(compr) / sizeof(compr[0]);
//    uncomprLen = 200;
//    err = compress2(compr, &comprLen, (const Bytef*)hello, len, 9);
//    if (err != Z_OK)
//    {
//        cerr << "compess error: " << err << '\n';
//        exit(1);
//    }
//    cout << "orignal size: " << len << " , compressed size : " << comprLen << '\n';
//    strcpy((char*)uncompr, "garbage");
//    err = uncompress(uncompr, &uncomprLen, compr, comprLen);
//    if (err != Z_OK)
//    {
//        cerr << "uncompess error: " << err << '\n';
//        exit(1);
//    }
//    cout << "orignal size: " << len << " , uncompressed size : " << uncomprLen << '\n';
//    if (strcmp((char*)uncompr, hello))
//    {
//        cerr << "BAD uncompress!!!\n";
//        exit(1);
//    }
//    else
//    {
//        cout << "uncompress() succeed: \n" << (char *)uncompr;
//    }
//
//    system("pause");
//    return 0;
//}


//#include <opencv2/opencv.hpp>
//
//int main()
//
//{
//
//    IplImage*src1 = cvLoadImage("E:\\Pictures\\37.jpg");
//
//    IplImage*src2 = cvLoadImage("E:\\Pictures\\38.jpg");
//
//    assert(src1);
//
//    //IplImage*dst = cvCreateImage(cvGetSize(src1), src1->depth, src1->nChannels);
//    IplImage*dst = cvCreateImage(cvGetSize(src2), src2->depth, src2->nChannels);
//
//    //cvSub(src1, src2, dst);
//    cvSub(src2, src1, dst);
//
//    cvShowImage("1", src1);
//
//    cvShowImage("2", src2);
//
//    cvShowImage("dst", dst);
//
//    cvWaitKey(0);
//
//}


//class A {
//public:
//    A() : i(5) { cout << "A::ctor, address: " << hex << (int)this << endl; }
//    void output() { cout << i << endl; }
//private:
//    int i;
//};
//
//class B {
//public:
//    B(A* a) : m_a(a)
//    {
//        cout << "B::ctor" << endl << "A::address: " << m_a << endl;
//        m_a->output();
//    }
//    void output()
//    {
//        //cout << "B::output()";
//        m_a->output();
//    }
//
//public:
//    A* m_a;
//};
//
//class C {
//public:
//    C() : m_b(&m_a)
//    {
//        cout << "C::ctor" << endl;
//    }
//    void output() 
//    { 
//        //cout << "C::output()"; 
//        //m_b.output();
//        m_a.output();
//    }
//
//private:
//    B m_b;
//    A m_a;
//};
//
//int main()
//{
//    C c;
//    c.output();
//    system("pause");
//    return 0;
//}


//std::bind绑定shared_ptr导致的引用计数增加
//当

//using msgCallback = std::function<void()>;
//
//class A {
//public:
//    ~A() { 
//        cout << "A::~A()" << endl; 
//    }
//    void output() {
//        cout << "A::output()" << endl;
//    }
//};
//
//class B {
//public:
//    ~B() {
//        cout << "B::~B()" << endl;
//    }
//    void setCallback(const msgCallback& cb) {
//        if (m_cb == nullptr)
//            m_cb = cb;
//    }
//    void resetCallback() {
//        m_cb = nullptr;
//    }
//private:
//    msgCallback m_cb;
//};

//int main()
//{
//    shared_ptr<B> spb = make_shared<B>();
//    {
//        shared_ptr<A> spa = make_shared<A>();   //use_count:1
//
//        list<shared_ptr<A>> lst;
//        lst.push_back(spa);     //use_count:2
//        cout << "count1: " << spa.use_count() << endl;
//        {
//            std::function<void()> f = std::bind(&A::output, spa);   //use_count:3
//            spb->setCallback(f);    //use_count:4
//            cout << "count2: " << spa.use_count() << endl;
//        }   //use_count:3
//        cout << "count3: " << spa.use_count() << endl;
//
//        if (!lst.empty())
//            lst.erase(lst.begin());     //use_count:2
//        cout << "count4: " << spa.use_count() << endl;
//    }   //use_count:1
//
//    //期望spa在lst.erase后就析构
//    //结果spb->m_cb还具有spa的一份引用，导致A不能按预期析构
//
//    system("pause");
//    return 0;
//}

//int main()
//{
//    {
//        shared_ptr<A> spa = make_shared<A>();   //use_count:1
//        shared_ptr<B> spb = make_shared<B>();
//
//        list<shared_ptr<A>> lst;
//        lst.push_back(spa);     //use_count:2
//        cout << "count1: " << spa.use_count() << endl;
//        {
//            std::function<void()> f = std::bind(&A::output, spa);   //use_count:3
//            spb->setCallback(f);    //use_count:4
//            cout << "count2: " << spa.use_count() << endl;
//        }   //use_count:3
//        cout << "count3: " << spa.use_count() << endl;
//
//        if (!lst.empty())
//            lst.erase(lst.begin());     //use_count:2
//        cout << "count4: " << spa.use_count() << endl;
//
//        spb->resetCallback();   //use_count:1
//        cout << "count5: " << spa.use_count() << endl;
//    }   //use_count:1
//
//    system("pause");
//    return 0;
//}



//int main()
//{
//    {
//        //A* a = new A[5];
//        A* a = new A;
//        delete[] a;
//    }
//
//    system("pause");
//    return 0;
//}


#include <iostream>
#include <typeinfo>
using namespace std;

//class A
//{
//public:
//    /*virtual*/ void Print() { cout << "This is class A." << endl; }
//};
//
//class B : public A
//{
//public:
//    void Print() { cout << "This is class B." << endl; }
//};
//
//int main()
//{
//    A *pA = new B();
//    cout << typeid(pA).name() << endl; // class A *
//    cout << typeid(*pA).name() << endl; // class B
//
//    system("pause");
//    return 0;
//}


class Base1 {
public:
    Base1() { cout << "Base1::Base1()" << endl; }
    virtual void f() { cout << "Base1::f()" << endl; }
    virtual void g() { cout << "Base1::g()" << endl; }
    virtual void h() { cout << "Base1::h()" << endl; }
};

class Base2 {
public:
    Base2() { cout << "Base2::Base2()" << endl; }
    virtual void f() { cout << "Base2::f()" << endl; }
    virtual void g() { cout << "Base2::g()" << endl; }
    virtual void h() { cout << "Base2::h()" << endl; }
};

class Derived : public Base1, public Base2 {
public:
    Derived() { cout << "Derived::Derived()" << endl; }
    void f() { cout << "Derived::f()" << endl; }
    virtual void g1() { cout << "Derived::g1()" << endl; }
};

//void printDerived(Derived &d)
//{
//    cout << endl << "print all vtable:" << endl;
//    int i = 0;
//    typedef void(*Fcn)();
//
//    cout << "Base" << i + 1 << "::vtable:" << endl;
//    for (int j = 0; j < 4; ++j)
//    {
//        Fcn vfcn = (Fcn)*((int*)*((int*)&d + i) + j);
//        vfcn();
//    }
//    ++i;
//
//    cout << "Base" << i + 1 << "::vtable:" << endl;
//    for (int j = 0; j < 3; ++j)
//    {
//        Fcn vfcn = (Fcn)*((int*)*((int*)&d + i) + j);
//        vfcn();
//    }
//}
typedef void(*PFUNC)(void);


void printDerived(Derived &d)
{
    cout << "Function address in virtual function table:" << endl;
    for (int i = 0; i < 7; i++) {
        cout << ((int **)(*(int *)(&d)))[i] << endl;
    }

    PFUNC pfunc;
    for (int i = 0; i < 4; ++i)
    {
        pfunc = ((PFUNC*)(*((int *)(&d) + 0)))[i];
        if (pfunc)
            pfunc();
    }
    for (int i = 0; i < 3; ++i)
    {
        pfunc = ((PFUNC*)(*((int *)(&d) + 1)))[i];
        if (pfunc)
            pfunc();
    }
}


#include <iostream>

using namespace std;
typedef void(*PFUNC)(void);

//class Base {
//public:
//    virtual void f() { cout << "Base::f()" << endl; }
//    virtual void g() { cout << "Base::g()" << endl; }
//    virtual void h() { cout << "Base::h()" << endl; }
//private:
//    int a;
//    int b;
//};
//class Derive :public Base
//{
//public:
//    virtual void f1() { cout << "Derive::f1()" << endl; }
//    virtual void g1() { cout << "Derive::g1()" << endl; }
//    virtual void h1() { cout << "Derive::h1()" << endl; }
//private:
//    int a;
//    int b;
//};
//int main()
//{
//    Derive b;
//
//    //cout << "Object start address:" << &b << endl;//对象起始地址
//    //cout << "Virtual function table start address:";//V-Table起始地址
//    //cout << (int **)(*(int *)(&b)) << endl;//int **：二级指针，表示虚表指针为函数指针数组
//
//    cout << "Function address in virtual function table:" << endl;
//    for (int i = 0; i<6; i++) {
//        cout << ((int **)(*(int *)(&b)))[i] << endl;
//    }
//
//    PFUNC pfunc;
//    for (int i = 0; i<6; i++) {
//        pfunc = ((PFUNC*)(int **)(*(int *)(&b)))[i];
//        pfunc();
//    }
//
//    return 0;
//}

void test_5_27()
{
    Derived d;
    printDerived(d);
    d.Base1::g();
}




//int main()
//{
//    //test_5_27();
//    test_5_31();
//
//    system("pause");
//    return 0;
//}


