#include <QCoreApplication>

#include<iostream>
#include "thread_guard.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::cout<<"WTF:"<<std::endl;

    return a.exec();
}
