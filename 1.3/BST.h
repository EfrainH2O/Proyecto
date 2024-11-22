#pragma once
#include "nodeT.h"
#include <iostream>

using namespace std;
template <class T>
class BST {
  protected:
    nodeT<T> *root;
    void clean(nodeT<T> *);
    void preorder(nodeT<T> *);
    void inorder(nodeT<T> *);
    void postorder(nodeT<T> *);
  public:
    BST();
    ~BST();
    bool search(T);
    virtual void add(T);
    virtual void erase(T);
    void preorder();
    void inorder();
    void postorder();
    void bylevel();
};

template <class T>
BST<T>::BST() {
    root = nullptr;
}

template <class T>
BST<T>::~BST() {
    clean(root);
}

template <class T>
void BST<T>::clean(nodeT<T> *p) {
    if (p == nullptr)
        return;

    clean(p->getLeft());
    clean(p->getRight());
    //cout << "delete " << p << " " << p->getData() << endl;
    delete p;
}

template <class T>
bool BST<T>::search(T data) {
    nodeT<T> *p = root;
    while (p != nullptr) {
        if (p->getData() == data) {
            return true;
        }
        else {
            p = (p->getData() > data ? p->getLeft() : p->getRight());
        }
    }
    return false;
}

template <class T>
void BST<T>::add(T data) {
    if (search(data))
        return; // data already exist in BST
    nodeT<T> *n = new nodeT<T>(data);
    //cout << "new " << n << " " << data << endl;
    nodeT<T> *p = root, *father = nullptr;
    while (p != nullptr) {
        father = p;
        p = (p->getData() > data ? p->getLeft() : p->getRight());
    }
    if (father == nullptr) {
        root = n; // is the first element to add
    }
    else if (father->getData() > data) {
        father->setLeft(n);
    }
    else {
        father->setRight(n);
    }
}

template <class T>
void BST<T>::erase(T data) {
    if (!search(data))
        return; // data does not exist in BST
    nodeT<T> *p = root, *father = nullptr;
    while (p->getData() == data) {
        father = p;
        p = (p->getData() > data ? p->getLeft() : p->getRight());
    }
    if (p->getLeft() == nullptr && p->getRight() == nullptr) {
        //cout << "erase " << p << " " << p->getData() << endl;
        delete p;
        if (father == nullptr) {
            root = nullptr; // was the only element in the BST
        }
        else if (father->getData() > data) {
            father->setLeft(nullptr);
        }
        else {
            father->setRight(nullptr);
        }
    }
    else if (p->getLeft() == nullptr || p->getRight() == nullptr) {
        nodeT<T> *son = p->getLeft() == nullptr ? p->getRight() : p->getLeft();
        if (father == nullptr) {
            root = son;
        }
        else if (father->getData() > data) {
            father->setLeft(son);
        }
        else {
            father->setRight(son);
        }
       // cout << "erase " << p << " " << p->getData() << endl;
        delete p;
    }
    else {
        nodeT<T> *s = p->getRight();
        while (s->getLeft() != nullptr) {
            s = s->getLeft();
        }
        T val = s->getData();
        erase(val);
        p->setData(val);
    }
    
}

template <class T>
void BST<T>::preorder() {
    preorder(root);
    cout << endl;
}

template <class T>
void BST<T>::inorder() {
    inorder(root);
    cout << endl;
}

template <class T>
void BST<T>::postorder() {
    postorder(root);
    cout << endl;
}

template <class T>
void BST<T>::preorder(nodeT<T> *p) {
    if (p != nullptr) {
        cout << p->getData() << " ";
        preorder(p->getLeft());
        preorder(p->getRight());
    }
}

template <class T>
void BST<T>::inorder(nodeT<T> *p) {
    if (p != nullptr) {
        inorder(p->getLeft());
        cout << p->getData() << " ";
        inorder(p->getRight());
    }
}

template <class T>
void BST<T>::postorder(nodeT<T> *p) {
    if (p != nullptr) {
        postorder(p->getLeft());
        postorder(p->getRight());
        cout << p->getData() << " ";
    }
}

#include <queue>
template <class T>
void BST<T>::bylevel() {
    queue<nodeT<T>*> q;
    nodeT<T> *p;
    if (root != nullptr)
        q.push(root);
    while (!q.empty()) {
        p = q.front();
        q.pop();
        cout << p->getData() << " ";
        if (p->getLeft() != nullptr)
            q.push(p->getLeft());
        if (p->getRight() != nullptr)
            q.push(p->getRight());
    }
    cout << endl;
}