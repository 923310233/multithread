//
// Created by 吴硕涵 on 2019-01-13.
//Descriptions:死锁的解决
//

#include <DeadLock.h>

#ifndef PARTONE_DEADLOCKREQUEST_H
#define PARTONE_DEADLOCKREQUEST_H

#endif //PARTONE_DEADLOCKREQUEST_H


Inventory g_inventory;

class Request {
public:
    void process() {
        MutexLockGuard mutexLockGuard(mutexLock);
        g_inventory.add(this);
    }

    ~Request() {
        MutexLockGuard mutexLockGuard(mutexLock);
        g_inventory.remove(this);
    }

//    函数不能作为inline函数优化
    void print() const __attribute__ ((noinline)) {

    }


private:
    MutexLock mutexLock;
};

