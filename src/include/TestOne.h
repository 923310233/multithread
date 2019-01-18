//
// Created by 吴硕涵 on 2019-01-08.
//

#ifndef PARTONE_TEST_H
#define PARTONE_TEST_H

#include <string.h>
#include <iostream>
#include <boost/bind/bind.hpp>
#include <gtest/gtest.h>

typedef int NUM[100];

//定义一个参数类型为(string,int)返回结果为string类型的函数指针F
typedef std::string(*F)(std::string, int);


class TestOne {
public:
    std::string func(std::string, int);

private:
};

TEST(test, show) {

}


#endif //PARTONE_TEST_H