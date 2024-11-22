#pragma once

template <class T>
class nodeT {
  private:
    T data;
    nodeT<T> *left, *right;
  public:
    nodeT();
    nodeT(T);
    T getData();
    nodeT<T>* getLeft();
    nodeT<T>* getRight();
    void setData(T);
    void setLeft(nodeT<T>*);
    void setRight(nodeT<T>*);
};

template <class T>
nodeT<T>::nodeT() {
    left = right = nullptr;
}

template <class T>
nodeT<T>::nodeT(T d) {
    data = d;
    left = right = nullptr;
}

template <class T>
T nodeT<T>::getData() {
    return data;
}

template <class T>
nodeT<T>* nodeT<T>::getLeft() {
    return left;
}

template <class T>
nodeT<T>* nodeT<T>::getRight() {
    return right;
}

template <class T>
void nodeT<T>::setData(T d){
    data = d;
}

template <class T>
void nodeT<T>::setLeft(nodeT<T>* p) {
    left = p;
}

template <class T>
void nodeT<T>::setRight(nodeT<T>* p) {
    right = p;
}