#pragma once

template <class T>
class Adjacency {
  private:
    T tag;
    Adjacency *next;
  public:
    Adjacency(T);
    T getTag();
    Adjacency<T>* getNext();
    void setNext(Adjacency<T>*);
};

template <class T>
Adjacency<T>::Adjacency(T t) {
    tag = t;
    next = nullptr;
}

template <class T>
T Adjacency<T>::getTag() {
    return tag;
}

template <class T>
Adjacency<T>* Adjacency<T>::getNext() {
    return next;
}

template <class T>
void Adjacency<T>::setNext(Adjacency<T>* n) {
    next = n;
}