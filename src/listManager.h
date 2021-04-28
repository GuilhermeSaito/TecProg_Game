#include "player1.h"
#include "element.h"

#pragma once

namespace Lists
{
    template <class KIND>
    class ListElement
    {
    private:
        Element<KIND> *first;
        Element<KIND> *last;

        //this "quantity" atribute has many utilities
        int quantity;

    public:
        ListElement()
        {
            this->first = NULL;
            this->last = NULL;

            this->quantity = 0;
        }

        ~ListElement()
        {
            Element<KIND> *aux = first;
            Element<KIND> *aux2 = first;
            while (aux != NULL)
            {
                aux = aux->getNext();
                delete aux2;
                aux2 = aux;
            }

            this->first = NULL;
            this->last = NULL;

            this->quantity = 0;
        }

        void setNull()
        {
            Element<KIND> *z = this->first;
            if (z->getNext() == NULL)
            {
                kill(z);
            }
            else
            {
                z = z->getNext();
                while (z != NULL && z->getNext() != NULL)
                {
                    Element<KIND> *zAux = z->getPrevious();
                    kill(zAux);
                    z = z->getNext();
                }
                kill(z);
            }

            this->first = NULL;
            this->last = NULL;

            this->quantity = 0;
        }

        void include(KIND *z)
        {
            Element<KIND> *aux = new Element<KIND>();
            aux->setInfo(z);
            //caso a lista esteja vazia
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

            this->quantity++;
        }

        void update(Entidade::Player::Player1 *p)
        {
            Element<KIND> *aux = this->first;
            while (aux != NULL)
            {
                aux->getInfo()->update(p);
                aux = aux->getNext();
            }
        }

        void render()
        {
            Element<KIND> *z = this->first;
            while (z != NULL)
            {
                z->getInfo()->render();
                z = z->getNext();
            }
        }

        void kill(Element<KIND> *z)
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

        Element<KIND> *getFirst()
        {
            return this->first;
        }

        const bool isEmpty() const
        {
            return (this->first == NULL);
        }

        void setQuantity(int i)
        {
            this->quantity = i;
        }
        const int getQuantity() const
        {
            return this->quantity;
        }
    };
}