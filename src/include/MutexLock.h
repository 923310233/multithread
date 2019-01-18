//
// Created by 吴硕涵 on 2019-01-07.
//

#ifndef PARTONE_MUTEX_H
#define PARTONE_MUTEX_H

#include <iostream>
#include <boost/noncopyable.hpp>

class MutexLock : boost::noncopyable {
public:
    MutexLock() : holder(0) {
        pthread_mutex_init(&mutex, nullptr);
    }

    ~MutexLock() {
        assert(holder == 0);
        pthread_mutex_destroy(&mutex);
    }

//    bool isLockedByThisThread()
//    {
//        return holder== CurrentThread::tid();
//    }


    void lock() {
        pthread_mutex_lock(&mutex);
//        holder_ = CurrentThread::tid();
    }

    //仅允许mutexLockGuard调用
    void unlock() {
        holder = 0;
        pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_t *getPthreadMutex() {
        return &mutex;
    }

private:
    pthread_mutex_t mutex;
    pid_t holder;

};

#endif //PARTONE_MUTEX_H


class MutexLockGuard : boost::noncopyable {
public:
    explicit MutexLockGuard(MutexLock &mutex) : mutexLock(mutex) {
        mutexLock.lock();
    }

    ~MutexLockGuard() {
        mutexLock.unlock();
    }

private:
    MutexLock &mutexLock;
};

#define MutexLockGuard(x) static_assert(false,"missing mutex guard var name")
