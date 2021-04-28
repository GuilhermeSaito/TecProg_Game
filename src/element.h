#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#pragma once

using namespace std;

namespace Lists
{
    template<class KIND>
    class Element
    {
    private:
        Element<KIND>* previous;
        Element<KIND>* next;

        KIND* info;

    public:
        Element()
        {
            this->previous = NULL;
            this->next = NULL;

            this->info = NULL;
        }

        ~Element()
        {
        }

        void setPrevious(Element<KIND>* p)
        {
            this->previous = p;
        }

        Element<KIND>* getPrevious()
        {
            return this->previous;
        }

        void setNext(Element<KIND>* n)
        {
            this->next = n;
        }

        Element<KIND>* getNext()
        {
            return this->next;
        }

        void setInfo(KIND* i)
        {
            this->info = i;
        }

        KIND* getInfo()
        {
            return this->info;
        }
    };
}