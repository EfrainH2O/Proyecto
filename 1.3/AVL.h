#pragma once
#include "BST.h"

template <class T>
class AVL : public BST<T> {
  private:
    bool isBalanced(T);
    bool isBalanced(nodeT<T> *p);
    int height(nodeT<T>*);
    void changeReference(nodeT<T>*,nodeT<T>*);
  public:
    AVL();
    ~AVL();
    void add(T);
    void erase(T data);
};

template <class T>
AVL<T>::AVL() {

}

template <class T>
AVL<T>::~AVL() {
    
}


template <class T>
bool AVL<T>::isBalanced(T data) {
    nodeT<T> *p = BST<T>::root;
    while (p->getData() != data) {
        if (!isBalanced(p)) {
            return false;
        }
        p = p->getData() > data ? p->getLeft() : p->getRight();
    }
    return true;
}

template <class T>
bool AVL<T>::isBalanced(nodeT<T> *p) {
    int hl, hr;
    hl = height(p->getLeft());
    hr = height(p->getRight());
    return !(hl > hr + 1 || hr > hl + 1);
}

template <class T>
void AVL<T>::add(T data) {
    BST<T>::add(data);
    if (isBalanced(data)) {
        return;
    }
    // look for the pivot
    nodeT<T> *p = BST<T>::root, *B;
    while (p->getData() != data) {
        if (!isBalanced(p)) {
            B = p;
        }
        p = p->getData() > data ? p->getLeft() : p->getRight();
    }
    nodeT<T> *A;
    if (B->getData() > data) {
        A = B->getLeft(); // we are on the left of B
        if (A->getData() > data) {
            // Single right rotation
            B->setLeft(A->getRight());
            A->setRight(B);
            changeReference(B,A);
        }
        else {
            // Double rotation to right
            nodeT<T> *C = A->getRight(); // right of A
            B->setLeft(C->getRight());
            A->setRight(C->getLeft());
            C->setLeft(A);
            C->setRight(B);
            changeReference(B,C);
        }
    }
    else {
        A = B->getRight(); // we are on the right of B
        if (A->getData() > data) {
            nodeT<T> *C = A->getLeft();
            B->setRight(C->getLeft());
            A->setLeft(C->getRight());
            C->setLeft(B);
            C->setRight(A);
            changeReference(B,C);
        }
        else {
            // RSI
            B->setRight(A->getLeft());
            A->setLeft(B);
            changeReference(B,A);
        }
    }
}

template <class T>
int AVL<T>::height(nodeT<T>* p) {
    if (p == nullptr)
        return 0;
    int hl, hr;
    hl = height(p->getLeft());
    hr = height(p->getRight());
    return (hl > hr ? hl : hr) + 1;
}

template <class T>
void AVL<T>::changeReference(nodeT<T>* B,nodeT<T>* A) {
    nodeT<T> *p = BST<T>::root, *q = nullptr;
    while (p != B) {
        q = p;
        p = p->getData() > B->getData() ? p->getLeft() : p->getRight();
    }
    if (q == nullptr) {
        BST<T>::root = A;
    }
    else if (q->getData() > B->getData()) {
        q->setLeft(A);
    }
    else {
        q->setRight(A);
    }
       
}

template <class T>
void AVL<T>::erase(T data) {
    BST<T>::erase(data);
    if (isBalanced(data)) {
        return;
    }
    // look for the pivot
    nodeT<T> *p = BST<T>::root, *B;
    while (p->getData() != data) {
        if (!isBalanced(p)) {
            B = p;
        }
        p = p->getData() > data ? p->getLeft() : p->getRight();
    }
    if (B->getData() > data) {
        // node deleted was in left side
        nodeT<T> *A = B->getRight();
        B->setRight(A->getLeft());
        A->setLeft(B);
        changeReference(B,A);
    }
    else {
        // node deleted was in right side
    }
}