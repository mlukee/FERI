#ifndef NALOGA0802_NODE_H
#define NALOGA0802_NODE_H

template<typename T>
class Node{
private:
    T value;
    Node * next;
public:
    Node(T value, Node * next = nullptr) : value(value), next(next){}
    T getValue() const{ return value; }
    void setValue(T value){ this->value = value; }
    Node * getNext() const { return next; }
    void setNext(Node * next) { this->next = next; }

};

#endif //NALOGA0802_NODE_H
