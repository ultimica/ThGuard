#ifndef _DUMMY_DCC__
#define _DUMMY_DCC__

#include <memory>


/////////////////////////////////////////////////////
//////////////////////////  Dummy Dcc & Dcc Task
//////////////////////////
//////////////////////////

struct DccTask
{
    void TaskAdd(unsigned int const loop);
    void TaskMinus(unsigned int const loop);
    void PrintX();
    int  x_{0};
};

struct DumyDCC
{
    void fun();
    int _x{100};
    int *_ptr_x;
    std::unique_ptr<DccTask>  task_ptr_{std::make_unique<DccTask>()};
};

#endif