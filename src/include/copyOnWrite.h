//
// Created by 吴硕涵 on 2019-01-13.
//Descriptions:读写锁
//

#ifndef PARTONE_COPYONWRITE_H
#define PARTONE_COPYONWRITE_H
#endif //PARTONE_COPYONWRITE_H


#include <MutexLock.h>
#include <iostream>
#include <Observer.h>

typedef std::vector<Foo> FooList;
typedef boost::shared_ptr<FooList> FooListPtr;

MutexLock mutexLock;
FooListPtr fooListPtr;

//shared_ptr 的unique()

//read
void traverse() {
    FooListPtr ptr; //栈上的局部变量

    MutexLockGuard lockGuard(mutexLock);
    ptr = fooListPtr;  //增加引用计数
    assert(!fooListPtr.unique());

    for (std::vector<Foo>::const_iterator it = ptr->begin(); it != ptr->end();
         ++it) {
        //如果仅为自己的线程 那么可以放心的在原地进行写操作
    }
}

void post(const Foo &foo) {
    MutexLockGuard lockGuard(mutexLock);
    //如果不是只有他在读取fooListPtr;
    if(!fooListPtr.unique()){
//        先复制一份
//        reset替换所管理的对象  注意这里重置的是指针
//        为何要reset 因为实际内存里的内容已经变了
        fooListPtr.reset(new FooList(* fooListPtr));
    }

    assert(fooListPtr.unique());
//    adds an element to the end
    fooListPtr->push_back(foo);
}

