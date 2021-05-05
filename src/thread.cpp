#include "thread.h"

namespace Thread
{
    pthread_mutex_t Thread::mutex = PTHREAD_MUTEX_INITIALIZER;

    Thread::Thread()
    {
    }
    Thread::~Thread()
    {
    }

    void* Thread::runThread(void* threadAux)
    {
        Thread* thread = static_cast<Thread*>(threadAux);

        if (thread != NULL)
        {
            thread->run();
        }
        else
            std::cout << "não foi possível rodar a thread" << std::endl;

        return NULL;
    }

    void Thread::start()
    {
        pthread_create(&thread_itself, NULL, runThread, static_cast<void*>(this));
    }
    void Thread::join()
    {
        pthread_join(thread_itself, NULL);
    }
    
    void Thread::yield()
    {
        sched_yield();
    }

    void Thread::lock()
    {
        pthread_mutex_lock(&mutex);
    }
    void Thread::unlock()
    {
        pthread_mutex_unlock(&mutex);
    }
}