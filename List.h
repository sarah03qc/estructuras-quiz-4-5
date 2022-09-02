#include "Node.h"
#include "event.h"

#ifndef LIST 

#define LIST 1

template <class T>
class List {
    private:
        Node<T> *first;
        Node<T> *last;
        int quantity;
        bool empty;
        Node<T> *searchPosition = NULL;
        Node<T> *searchBehind = NULL;

    public:
        List() {
            first = NULL;
            last = NULL;
            quantity = 0;
            empty = true;
        }

        void add(T *pData) {
            Node<T> *newNode = new Node<T>(pData);

            if (quantity>0) {
                this->last->setNext(newNode);
                newNode->setPrevious(this->last); //modif, el que era el ultimo nodo (antes) se asigna como el previo del newnode
            } else {
                this->first = newNode;
            }
            this->last = newNode;

            empty = false;
            quantity++;
        }

        Node<T>* getFirst() {
            return this->first;
        }

        int getSize() {
            return quantity;
        }

        bool isEmpty() {
            return !quantity;
        }

        T* find(int pPosition) {
            T* result = NULL;
            searchPosition = this->first;
            searchBehind = NULL;

            if (pPosition<getSize()) {
                while(pPosition>0) {
                    searchPosition = searchPosition->getNext();
                    searchBehind = searchPosition->getPrevious();   //modif, ahora podemos aprovechar que es doblemente enlazada
                    
                    pPosition--;
                }
                result = searchPosition->getData();
            }

            return result;
        }


//searchPosition->getPrevious()
        // es que si el position es mayor a la cantidad, entonces inserto al final
        void insert(int pPosition, T *pData) {
            
            if (pPosition<getSize() && first!=NULL) {
                Node<T> *newNodo = new Node<T>(pData);

                T* result = find(pPosition);
                
                newNodo->setNext(searchPosition);
                searchPosition->setPrevious(newNodo);  //modif, para que el 'previo' del siguiente nodo donde se desea insertar apunte al nodo nuevo 
                if (searchBehind!=NULL) {
                    searchBehind->setNext(newNodo);
                    newNodo->setPrevious(searchBehind);  //modif, el 'previo' del nodo nuevo va a ser el que esta antes de la posicion donde se desea insertar
                } else {
                    this->first = newNodo;
                }
                
                quantity++;
            } else {
                add(pData);
            }
        }

        bool remove(int pPosition) {
            bool result = false;
            if (first!=NULL && pPosition<getSize()) {
                Node<T> *search = first;
                if (pPosition!=0) {
                    T* data = find(pPosition);

                    searchBehind->setNext(searchPosition->getNext());
                    if(searchPosition->getNext()!=NULL) {  //modif, ponemos esta condicion por si es el ultimo, para no tener una excepcion por NULL
                        searchPosition->getNext()->setPrevious(searchBehind); //modif, que el siguiente de la posicion que se desea eliminar tenga como previo el anterior a la posicion a eliminar 
                    }

                    if (searchPosition==last) {
                        last = searchPosition->getPrevious();
                    }
                    searchPosition->setNext(NULL);
                    searchPosition->setPrevious(NULL); //modif, para 'desconectarlo', que el previo sea null
                } else {
                    first = first->getNext();
                    first->setPrevious(NULL);   //modif, como es el primero el que se elimina...
                    //...el segundo toma el lugar, pero ya no apunta a nada para atras porque elimina el 'former' primero
                    search->setNext(NULL);
                    delete search;
                }
                quantity--;
            }
            return result;
        } 
};

#endif