cmake_minimum_required(VERSION 3.13)

#设置项目名称
project(partOne)

set(BOOST_ROOT "/usr/local/include/boost")
# 查找boost的功能模块  在整个电脑上找包
find_package(Boost 1.67.0 COMPONENTS log thread system regex date_time REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})


#添加头文件搜索路径
include_directories(src/include)

#我们需要使用外部的文件夹  add_subdirectory命令，可以将指定的文件夹加到build任务列表中。
#add_subdirectory(./googletest)

#指定原始目录，不要忘记添加第二个默认参数 dir_srcs
#用于将当前目录下的所有源文件的名字保存在变量 DIR_SRCS 中
aux_source_directory(src/main dir_srcs)

set(CMAKE_CXX_STANDARD 14)

add_executable(partOne src/main/main.cpp src/main/MutexLock.cpp src/include/MutexLock.h src/main/Observer.cpp src/include/Observer.h src/main/Observable.cpp src/include/Observable.h src/main/TestOne.cpp src/include/TestOne.h src/main/Condition.cpp src/include/Condition.h src/main/Singleton.cpp src/include/Singleton.h src/include/copyOnWrite.h src/include/DeadLock.h src/include/DeadLockRequest.h src/include/InventoryAdvice.h src/include/CustomerData.h src/main/CustomerData.cpp)

#添加库文件搜索路径
#link_directories(${PROJECT_SOURCE_DIR}/googletest)

#需要添加googletest运行需要的pthread
set(LIBRARIES pthread)


#添加要编译的可执行文件。注意，通过变量WORK来编译
#set(WORK ${dir_srcs})
#add_executable(work ${WORK})

#连接gtest与Boost库
target_link_libraries(partOne gtest ${Boost_LIBRARIES})

