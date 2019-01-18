//
// Created by 吴硕涵 on 2019-01-13.
//Descriptions:死锁的解决
//两个类互相引用的问题
//

#ifndef PARTONE_DEADLOCK_H
#define PARTONE_DEADLOCK_H

#endif //PARTONE_DEADLOCK_H

#include <iostream>
#include <MutexLock.h>
#include <set>

class Request;

class Inventory {
public:
    void add(Request *request_) {
        MutexLockGuard mutexLockGuard(mutexLock);
        requests.insert(request_);
    };

    void remove(Request *rq) {
        MutexLockGuard mutexLockGuard(mutexLock);
        requests.erase(rq);
    }

//    如何把Request的printAll移除 Inventory的PrintALl的临界区
//    方法1：开销可能较大 因为复制了所有的元素
    void printAllOne() const {
        std::set<Request *> _request;
        {
            MutexLockGuard lockGuard(mutexLock);
            _request = requests;
        }
        std::set<Request *>::const_iterator iterator = _request.begin();
        while(iterator!=_request.end()){
//            (*iterator) -> printAll();
        }
        iterator++;
    }


private:
    mutable MutexLock mutexLock;
    std::set<Request *> requests;
};




