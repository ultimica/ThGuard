#include <QCoreApplication>

#include<iostream>
#include "thread_guard.hpp"

//#define GETDCCTASKPTR(INPUT) INPUT.GetEnc().GetData().task_ptr_
#define GETDCCTASKPTR(INPUT) INPUT.data_.task_ptr_

struct ThreadFun
{

    void RunTh1(Utilizer &input)
    {
        th1_=std::make_unique<std::thread>([&input](){
            for(int i=0;i<100;i++)
            {
                GETDCCTASKPTR(input)->TaskAdd(5);
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        });
    }

    void RunTh2(Utilizer &input)
    {
            th2_=std::make_unique<std::thread>([&input](){
            for(int i=0;i<100;i++)
            {
                GETDCCTASKPTR(input)->TaskMinus(5);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        });
    }
    std::unique_ptr<std::thread> th1_;
    std::unique_ptr<std::thread> th2_;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Utilizer g_util;
    ThreadFun thfun;

    thfun.RunTh1(g_util);
    thfun.RunTh2(g_util);
    return a.exec();
}
