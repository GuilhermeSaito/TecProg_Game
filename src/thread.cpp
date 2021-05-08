#include "thread.h"

using namespace Tred;

Thread::Thread()
{
}
Thread::~Thread()
{
}

void *Thread::runThread(void *threadAux)
{
    Thread *thread = static_cast<Thread *>(threadAux);

    if (thread != NULL)
        thread->run();
    else
        std::cout << "Thread falhou" << std::endl;
}

void Thread::start()
{
    int status = pthread_attr_init(&tAttribute);
    status = pthread_attr_setscope(&tAttribute, PTHREAD_SCOPE_SYSTEM);
    if (status != 0)
        std::cout << "falha ao iniciar atributo da thread.\n";

    status = pthread_create(&thread_itself, &tAttribute, Thread::runThread, (void *)this);
    if (status != 0)
        std::cout << "falha ao iniciar a thread.\n";

    status = pthread_attr_destroy(&tAttribute);
    if (status != 0)
        std::cout << "falha ao destruir atributo da thread.\n";
}
void Thread::join()
{
    if (pthread_join(thread_itself, NULL) != 0)
        std::cout << "Comando join falhou.\n";
}
void Thread::yield()
{
    sched_yield();
}