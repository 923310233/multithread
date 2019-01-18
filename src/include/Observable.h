//
// Created by 吴硕涵 on 2019-01-07.
//

#ifndef PARTONE_OBSERVABLE_H
#define PARTONE_OBSERVABLE_H

#include <iostream>
#include <MutexLock.h>
#include <Observer.h>
#include <boost/noncopyable.hpp>
#include <vector>

class Observable {
public:
    void register_(std::weak_ptr<Observer> ptr);

    void unregister(std::weak_ptr<Observer> ptr);

    void notifyObservsers() {
        MutexLock
    }

private:
    mutable MutexLock mutexLock;
    std::vector<std::weak_ptr<Observer>> observers;
    typedef std::vector<std::weak_ptr<Observer>>::iterator iterator;

};

#endif //PARTONE_OBSERVABLE_H

