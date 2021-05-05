#include <pthread.h>
#include <iostream>

#pragma once
namespace Thread
{
//classe criada para administrar as funções de thread
    class Thread
    {
    protected:
        pthread_t thread_itself;
        static pthread_mutex_t mutex;

        static void* runThread(void* threadAux);
        
    public:
        Thread();
        ~Thread();

        virtual void run() = 0;

        void start();
        void join();

        //coloca a thread no último lugar da fila, dando permissão para a próxima rodar
        void yield();

        void lock();
        void unlock();
    };
}