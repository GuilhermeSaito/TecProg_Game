#include <pthread.h>
#include <iostream>

#pragma once
namespace Tred
{
    //classe criada para administrar as funções de thread
    class Thread
    {
    protected:
        pthread_t thread_itself;
        pthread_attr_t tAttribute;

        static void *runThread(void *);

    public:
        Thread();
        ~Thread();

        virtual void run() = 0;

        void start();
        void join();
        void yield();
    };
}