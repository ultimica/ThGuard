#ifndef _TH_GUARD_
#define _TH_GUARD_


#include<mutex>
#include<thread>
#include<iostream>
#include <memory>

template<typename EncDataType>
struct Encaptor
{
    Encaptor(EncDataType * enc) : _data(enc)
    {
        recursive_mutex_.lock();
        std::cout<<"[CTOR] Start Lock"<<std::endl;
    }

    Encaptor(Encaptor && input)=default;

    Encaptor(Encaptor const &input) : _data(input._data)
    {
        std::cout<<"[Copy]"<<std::endl;
    }

    ~Encaptor()
    {
        std::cout<<"[DEAD] End Unlock"<<std::endl;
        recursive_mutex_.unlock();
    }
    EncDataType &GetData()
    {
        return (*_data);
    }

    int *_ptr_x;

    EncDataType *_data;
    static std::recursive_mutex recursive_mutex_;
};

template<typename EncDataType>
std::recursive_mutex Encaptor<EncDataType>::recursive_mutex_;

/////////////////////////////////////////////////////
//////////////////////////  Dummy Dcc & Dcc Task
//////////////////////////
//////////////////////////

struct DccTask
{
    void TaskAdd(unsigned int const loop)
    {
        for(int i=0;i!=loop;++i)
        {
            ++x_;
            PrintX();
        }
    }

    void TaskMinus(unsigned int const loop)
    {
        for(int i=0;i!=loop;++i)
        {
            --x_;
            PrintX();
        }
    }

    void PrintX()
    {
        std::cout<<"X Value=>"<<x_<<"\tPrint Thread=>"<<std::this_thread::get_id()<<std::endl;
    }
    int  x_{0};
};
struct DumyDCC
{
    void fun()
    {
        std::cout<<"AAAAADKDKDKDKDD=>"<<std::endl;
    }
int _x{100};
int *_ptr_x;
std::unique_ptr<DccTask>  task_ptr_{std::make_unique<DccTask>()};
};

#define GETSETVAR(Type,var) Type &Get() \
                        {       \
                            return gobj.GetEnc().GetData()->var;    \
                        }

struct Utilizer
{
    Encaptor<DumyDCC> GetEnc()
    {
        return Encaptor<DumyDCC>(&data_);
    }

    DumyDCC data_;
};



#endif
