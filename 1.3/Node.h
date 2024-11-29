#pragma once
#include "Adjacency.h"

enum status {
    waiting,
    processed,
    ready,
};

template <class T>
class Node {
  private:
    T tag;
    int count;
    int Ady;
    Node<T>* next;
    Adjacency<T>* first;
  public:
    Node(T);
    ~Node();
    status s;
    T getTag();
    Node<T>* getNext();
    void increaseCount();
    void setNext(Node<T>*);
    void setAdyacency(Node<T>*);
    void delAdyacency(Node<T>*);
    bool isAdyacency(Node<T>*);
    int getCount();
    int getAdyacencies();
    int getAdy();
};

template <class T>
Node<T>::Node(T t) {
    tag = t;
    next = nullptr;
    first = nullptr;
    count = 1 ;
    Ady = 0;
}

template <class T>
Node<T>::~Node() {
    Adjacency<T> *p = first, *q;
    while (p != nullptr) {
        q = p->getNext();
        delete p;
        p = q;
    }
}

template <class T>
T Node<T>::getTag() {
    return tag;
}

template <class T>
int Node<T>::getAdy(){
    return Ady;
}
template <class T>
void Node<T>::increaseCount(){
    count++;
}

template <class T>
int Node<T>::getCount(){
    return count;
}

template <class T>
int Node<T>::getAdyacencies(){
    Adjacency<T>* p = first;
    int i = 0;
    while(p != nullptr){
        cout<<p->getTag()<<' ';
        p = p->getNext();
        i++;
    } 
    cout<</*i==0? "NoAdyacencies" : i <<*/endl;
    return i;
}


template <class T>
Node<T>* Node<T>::getNext() {
    return next;
}

template <class T>
void Node<T>::setNext(Node<T>* n) {
    next = n;
}

template <class T>
void Node<T>::setAdyacency(Node<T>* b) {
    Ady++;
    Adjacency<T> *c = new Adjacency<T>(b->getTag());
    c->setNext(first);
    first = c;
}

template <class T>
void Node<T>::delAdyacency(Node<T>* b){
    Ady--;
    Adjacency<T> *p = first, *q = nullptr;
    while (p != nullptr) {
        if (p->getTag() == b->getTag())
            break;
        q = p;
        p = p->getNext();
    }
    if (p != nullptr) {
        if (q != nullptr) {
            q->setNext(p->getNext());
        }
        else {
            first = p->getNext();
        }
        delete p;
    }
}

template <class T>
bool Node<T>::isAdyacency(Node<T>* b){
    Adjacency<T> *p = first;
    while (p != nullptr) {
        if (p->getTag() == b->getTag())
            return true;
        p = p->getNext();
    }
    return false;
}
