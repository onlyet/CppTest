//#pragma once
//#include <memory>
//#include <mutex>    //to use std::call_once
//
//class Cat
//{
//public:
//    Cat();
//    ~Cat();
//};
//
//class Dog
//{
//public:
//    Dog();
//    ~Dog();
//};
//
//class Cat_Singleton 
//{
//public:
//    static Cat_Singleton& GetInstance()
//    {
//        static Cat_Singleton m_instance;
//        return m_instance;
//    }
//private:
//    Cat_Singleton();
//    ~Cat_Singleton();
//};
//
//class Dog_Singleton
//{
//public:
//    static Dog_Singleton& GetInstance()
//    {
//        static Dog_Singleton m_instance;
//        return m_instance;
//    }
//private:
//    Dog_Singleton();
//    ~Dog_Singleton();
//};
//
//
//template <class T>
//class Singleton
//{
//public:
//    static T& instance()
//    {
//        //qCallOnce(init, flag);
//        std::call_once(onceFlag, init);
//        //static bool callOnce = true;
//        //if(callOnce)
//        //{
//        //    callOnce = false;
//        //    tptr.reset(new T);
//        //}
//        return *tptr;
//    }
//
//    static void init()
//    {
//        tptr.reset(new T);
//    }
//
//public:
//    Singleton() {};
//    ~Singleton() {};
//    //Q_DISABLE_COPY(Singleton)
//
//    //static QScopedPointer<T> tptr;
//    //static QBasicAtomicInt flag;
//    static unique_ptr<T> tptr;
//    static std::once_flag onceFlag;
//};
//
//template<class T> unique_ptr<T> Singleton<T>::tptr(nullptr);
//template<class T> std::once_flag Singleton<T>::onceFlag;
//
//class Cat_Singleton_new
//{
//public:
//    static Cat_Singleton_new& GetInstance()
//    {
//        //m_spInstance.reset(new Cat_Singleton_new);
//        //return *m_spInstance;
//        return Cat_Singleton_new();
//    }
//    ~Cat_Singleton_new();
//
//private:
//    Cat_Singleton_new();
//
//private:
//    static shared_ptr<Cat_Singleton_new> m_spInstance;
//};
//
//class Dog_Singleton_new
//{
//public:
//    static Dog_Singleton_new& GetInstance()
//    {
//        m_spInstance.reset(new Dog_Singleton_new);
//        return *m_spInstance;
//    }
//    ~Dog_Singleton_new();
//
//private:
//    Dog_Singleton_new();
//
//private:
//    static shared_ptr<Dog_Singleton_new> m_spInstance;
//};