#include "zombie.h"
#include "element.h"

#pragma once

template<class KIND>
class ListElement
{
private:
    Element<KIND>* first;
    Element<KIND>* last;

public:
    ListElement()
    {
        this->first = NULL;
        this->last = NULL;
    }

    ~ListElement()
    {
        this->first = NULL;
        this->last = NULL;
    }

    void setNull()
    {
        this->first = NULL;
        this->last = NULL;
    }

    void include(KIND* z)
    {
        Element<KIND>* aux = new Element<KIND>();
        aux->setInfo(z);
        if (this->first == NULL)
        {
            this->first = aux;
            this->last = aux;
        }
        else
        {
            this->last->setNext(aux);
            aux->setPrevious(this->last);
            this->last = aux;
        }
    }

    void update(float posx)
    {
        Element<KIND>* aux = this->first;
        while (aux != NULL)
        {
            aux->getInfo()->update(posx);
            aux = aux->getNext();
        }
    }

    void render(sf::RenderWindow& window)
    {
        Element<KIND>* z = this->first;
        while( z != NULL)
        {
            z->getInfo()->render(window);
            z = z->getNext();
        }
    }

    void kill(Element<KIND>* z)
    {
        // Se for o primeiro da lista a morrer
        if (z == this->first)
        {
            // Se ele for o único elemento sobrando
            if (z->getNext() == NULL)
            {
                this->first = NULL;
                this->last = NULL;
            }
            else
            {
                z->getNext()->setPrevious(NULL);
                this->first = z->getNext();
            }
        }
        // Se for o último elemento
        else if (z == this->last)
        {
            z->getPrevious()->setNext(NULL);
            this->last = z->getPrevious();
        }
        //caso esteja no meio da lista
        else
        {
            z->getPrevious()->setNext(z->getNext());
            z->getNext()->setPrevious(z->getPrevious());
        }
            delete (z);
    }

    Element<KIND>* getFirst()
    {
        return this->first;
    }

    const bool isEmpty() const 
    {
        return (this->first == NULL);
    }


};
