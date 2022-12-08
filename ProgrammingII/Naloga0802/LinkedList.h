#ifndef NALOGA0802_LINKEDLIST_H
#define NALOGA0802_LINKEDLIST_H

#include "Node.h"
template<typename T>
class LinkedList{
private:
    Node<T>* head = nullptr;
public:
    ~LinkedList(){
        Node<T> *current = head;
        while(current->getNext()!= nullptr){
            Node<T>* tmp = current->getNext();
            delete current;
            current = tmp;
        }
    }
    bool isEmpty() const{
        if(head == nullptr)
            return true;
        return false;
    }
    int getSize() const{
        Node<T> *current = head;
        int size = 0;
        while(current!= nullptr){
            size++;
            current = current->getNext();
        }
        return size;
    }

    void add(T value){
        Node<T> * newNode = new Node<T>(value);
        if(head == nullptr){
            head = newNode;
            return;
        }
        Node<T> * temp = head;
        while(temp->getNext() != nullptr){
            temp = temp->getNext();
        }
        temp->setNext(newNode);
    }

    T at(unsigned int index){
        Node<T> * current = head;
        for(int i = 0;i< index && current->getNext() != nullptr;i++)
            current = current->getNext();
        return current->getValue();
    }

    void removeAt(int index){
        int size = getSize();
        if(index >= size)
            return;
        if(index == 0){
            Node<T> * current = head;
            head = head->getNext();
            delete current;
            return;
        }
        Node<T> * current = head;
        for(int i =0;i<index-1;i++){
            current = current->getNext();
        }
        Node<T> * tmp = current->getNext()->getNext();
        delete current->getNext();
        current->setNext(tmp);
    }
};

#endif //NALOGA0802_LINKEDLIST_H
