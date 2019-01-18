//
// Created by 吴硕涵 on 2019-01-18.
//Descriptions:
//

#include <CustomerData.h>

int CustomerData::query(const std::string &customer, const std::string &stock) const {
//    用引用计数+1的方法 用局部变量来持有  防止并发修改
//    其核心在于 读端 与 写端
//    写端会判断引用计数是否为1 如果为1 说明目前只有他自己在占有资源
//    读端会通过局部变量把引用计数+1
    MapPtr data = getData();   //暂时加锁 阻塞一下

    ListMap::const_iterator iterator = data->find(customer);

    if (iterator != data->end()) {
        return findEntry(iterator->second, stock);
    } else {
        return -1;
    }

}

void CustomerData::update(const std::string &customer, const EntryList &entryList) {
    MutexLockGuard mutexLockGuard(mutexLock);//全程持锁

    //如果有人正在读
    if(!data.unique()){
//        新建智能指针 智能指针里拷贝一下共享数据的副本  因为 原本 正有线程在读写
        MapPtr newMapPtr(new ListMap(*data));

        //修改后再替换
        data.swap(newMapPtr);
        //因为query()并不全程加锁  只在读数据的时候getData()时加一下锁 暂时阻塞
        
    }
}

