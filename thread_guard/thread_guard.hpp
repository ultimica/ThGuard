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


#define GET_ENC_DATA_MEMBER_VAR(EncaptorObj, var) EncaptorObj.GetEnc().GetData().var

#endif
