//
// Created by 吴硕涵 on 2019-01-18.
//Descriptions:
// 一个多线程的C++程序
// 工作线程只读(加读锁) 背景线程读写(加写锁)  写锁优先级高 会阻塞后面的读锁
// 具体实现见CPP文件
//

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <MutexLock.h>
#include <string.h>
#include <map>


#ifndef PARTONE_CUSTOMERDATA_H
#define PARTONE_CUSTOMERDATA_H


class CustomerData : boost::noncopyable {
public:
    CustomerData() : data(new ListMap) {}

    int query(const std::string &customer, const std::string &stock) const;


private:
    typedef std::pair<std::string, int> Entry;
    typedef std::vector<Entry> EntryList;
    typedef std::map<std::string, EntryList> ListMap;
    typedef boost::shared_ptr<ListMap> MapPtr;
    MapPtr data;
    mutable MutexLock mutexLock;

    MapPtr getData() const {
        MutexLockGuard lockGuard(mutexLock);
        return data;
    }

    void update(const std::string& customer, const EntryList & entryList);

    static int findEntry(const EntryList &entryList, const std::string stock);

};


#endif //PARTONE_CUSTOMERDATA_H
