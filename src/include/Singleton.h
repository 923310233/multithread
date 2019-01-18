//
// Created by 吴硕涵 on 2019-01-11.
//Descriptions:单例的实现
//C++ private static的init
//

#ifndef PARTONE_SINGLETON_H
#define PARTONE_SINGLETON_H

#include <boost/noncopyable.hpp>
#include <pthread.h>

//LinuxThreads使用互斥锁和条件变量保证由pthread_once()指定的函数执行且仅执行一次，
//而once_control则表征是否执行过。

template<typename T>
class Singleton : boost::noncopyable {
public:
    static T &instance() {
        pthread_once(&pthreadOnce, &Singleton::init);
        return *value;
    }

    static void init() {
        value = new T();
    }

private:
    Singleton();

    ~Singleton();

    //不能在类内初始化static变量
    static pthread_once_t pthreadOnce;
    static T *value;
};

//必须在类外初始化 private static
template<typename T>
pthread_once_t Singleton<T>::pthreadOnce = PTHREAD_ONCE_INIT;

template<typename T>
T *Singleton<T>::value = NULL;


//初值为PTHREAD_ONCE_INIT的pthreadOnce 变量保证函数init()在本进程执行序列中仅执行一次。



#endif //PARTONE_SINGLETON_H


