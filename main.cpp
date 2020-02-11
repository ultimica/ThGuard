#include <QCoreApplication>

#include <iostream>
#include <functional>
#include <vector>
#include "thread_guard.hpp"
#include "dummy_dcc.h"

///This is thread guarded method
#define GETDCCTASKPTR(INPUT)  GET_ENC_DATA_MEMBER_VAR(INPUT,task_ptr_) //INPUT.GetEnc().GetData().task_ptr_

///This is un-guarded method
//#define GETDCCTASKPTR(INPUT) INPUT.data_.task_ptr_



struct Utilizer
{
    Encaptor<DumyDCC> GetEnc()
    {
        return Encaptor<DumyDCC>(&data_);
    }

    DumyDCC data_;
};



struct PressureTest
{
    struct LoopTime{const unsigned int loop_cnt_;};

    template<typename Functor>
    void RunTh(LoopTime &&looptimes, Functor functor)
    {
        th_=std::make_unique<std::thread>(
            [lopcnt=looptimes.loop_cnt_,functor]()
            {
                for(unsigned int i=0;i<lopcnt;i++)
                {
                    functor();
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                }
            }
        );
    }
    std::unique_ptr<std::thread> th_;
};

using PressLoop=PressureTest::LoopTime;

struct ThreadFun
{

    ThreadFun()
    {
        for(int i=0;i<10;i++)
            th_vec_.emplace_back(std::make_unique<PressureTest>());
    }

    ///////////////////////////////////////////////////////////////
    ////Simple Thread Using~~
    void RunTh1(Utilizer &input)
    {
        th1_=std::make_unique<std::thread>([&input](){
            for(unsigned int i=0;i<100;i++)
            {
               // GETDCCTASKPTR(input)->TaskAdd(10);
                auto encaper=input.GetEnc();
                encaper.GetData().task_ptr_->TaskAdd(10);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        });
    }

    void RunTh2(Utilizer &input)
    {
        th2_=std::make_unique<std::thread>([&input](){
            for(unsigned int i=0;i<100;i++)
            {
               // GETDCCTASKPTR(input)->TaskMinus(10);
                auto encaper=input.GetEnc();
                encaper.GetData().task_ptr_->TaskMinus(10);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        });
    }
    std::unique_ptr<std::thread> th1_;
    std::unique_ptr<std::thread> th2_;

    ///////////////////////////////////////////////////////////////
    ////Thread Pool Using~~
    void RunThreadPool(Utilizer &input)
    {
        bool isAdd=true;
        for(auto &thtest : th_vec_)
        {
            if(isAdd)
                thtest->RunTh(PressLoop{100},
                    [&input]()
                    {
                            GETDCCTASKPTR(input)->TaskAdd(10);
                            std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    }
                );
            else
                thtest->RunTh(PressLoop{100},
                    [&input]()
                    {
                            GETDCCTASKPTR(input)->TaskMinus(10);
                            std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    }
                );
            
            isAdd=!isAdd;
        }        
        
    }

    std::vector<std::unique_ptr<PressureTest>>   th_vec_;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Utilizer g_util;
    ThreadFun thfun;

    // thfun.RunTh1(g_util);
    // thfun.RunTh2(g_util);
    thfun.RunThreadPool(g_util);

    while(1)
    {
        GETDCCTASKPTR(g_util)->TaskMinus(3);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return a.exec();
}
