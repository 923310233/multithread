//
// Created by 吴硕涵 on 2019-01-18.
//Descriptions:
// 把request的Print移除PrintALl的临界区  前提是遍历期间没有人修改
// 解决了竟态问题
//

//
//由于两个或者多个进程竞争使用不能被同时访问的资源，
//使得这些进程有可能因为时间上推进的先后原因而出现问题，
//这叫做竞争条件（Race Condition）。

#include <MutexLock.h>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <set>

#ifndef PARTONE_INVENTORYADVICE_H
#define PARTONE_INVENTORYADVICE_H

#endif //PARTONE_INVENTORYADVICE_H

//    其核心在于 读端 与 写端
//    写端会判断引用计数是否为1 如果为1 说明目前只有他自己在占有资源
//    读端会通过局部变量把引用计数+1

class Request;

typedef boost::shared_ptr<Request> RequestPtr;

class Inventory {
public:
    void printAll() const;

private:
    typedef std::set<RequestPtr> RequestPtrSet;
    typedef boost::shared_ptr<RequestPtrSet> RequestPtrSetPtr;
    mutable MutexLock mutexLock;
    RequestPtrSetPtr requestPtrPtr;


    RequestPtrSetPtr getData() const {
        MutexLockGuard lockGuard(mutexLock);
        return requestPtrPtr;
    }
};

class Request : public boost::enable_shared_from_this<Request> {
public:
    Request() : x(0) {}

    ~Request() {
        x = -1;
    }

    void print() const __attribute__ ((noinline)) {
        MutexLockGuard lock(mutexLock);
        // ...
        printf("print Request %p x=%d\n", this, x);
    }

private:
    mutable MutexLock mutexLock;
    int x;

};

void Inventory::printAll() const {
    //智能指针集合的智能指针  一块内存被至少两个智能指针指着
     RequestPtrSetPtr requestPtrSetPtr = getData();
    //使用智能指针管理 set  增加引用计数

    for (std::set<RequestPtr>::const_iterator iterator = requestPtrSetPtr->begin();
         iterator != requestPtrSetPtr->end(); iterator++) {
        (*iterator)->print();
    }

}
