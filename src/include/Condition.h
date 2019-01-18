//
// Created by 吴硕涵 on 2019-01-08.
//Descriptions:条件变量的封装
//


#ifndef PARTONE_CONDITION_H
#define PARTONE_CONDITION_H

#include <boost/noncopyable.hpp>
#include <MutexLock.h>

//自造轮子
//Pthreads库

class Condition : boost::noncopyable {
public:
    explicit Condition(MutexLock &lock) : mutexLock(lock) {
        pthread_cond_init(&pthreadCond, NULL);//指针初始化
    }

    ~Condition() {
        pthread_cond_destroy(&pthreadCond);
    }

    void wait() {
        pthread_cond_wait(& pthreadCond,mutexLock.getPthreadMutex());
    }

    void notify() {
        pthread_cond_signal(&pthreadCond);
    }

    void notifyAll(){
        pthread_cond_broadcast(&pthreadCond);
    }

private:
    MutexLock &mutexLock;
    pthread_cond_t pthreadCond;//条件变量

};


#endif //PARTONE_CONDITION_H

