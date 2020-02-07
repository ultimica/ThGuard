#include "dummy_dcc.h"

#include <iostream>
#include <thread>

void DccTask::TaskAdd(unsigned int const loop)
{
    for(unsigned int i=0;i!=loop;++i)
    {
        ++x_;
        PrintX();
    }
}

void DccTask::TaskMinus(unsigned int const loop)
{
    for(unsigned int i=0;i!=loop;++i)
    {
        --x_;
        PrintX();
    }
}

void DccTask::PrintX()
{
    std::cout<<"X Value=>"<<x_<<"\tPrint Thread=>"<<std::this_thread::get_id()<<std::endl;
}


//////////////////////////////////////////////
void DumyDCC::fun()
{
    std::cout<<"AAAAADKDKDKDKDD=>"<<std::endl;
}
