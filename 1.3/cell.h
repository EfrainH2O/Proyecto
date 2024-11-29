#pragma once

enum status {
    empty,
    ocuppied,
    deleted,
};

template <class T>
class cell {
  private:
    status s;
    T data;
  public:
    cell();
    T getData();
    void setData(T);
    void delData();
    bool isEmpty();
    bool isOcuppied();
    bool isDeleted();
};


template <class T>
cell<T>::cell() {
    s = empty;
}

template <class T>
T cell<T>::getData() {
    return data;
}

template <class T>
void cell<T>::setData(T d) {
    data = d;
    s = ocuppied;
}

template <class T>
void cell<T>::delData() {
    s = deleted;
}

template <class T>
bool cell<T>::isEmpty() {
    return s == empty;
}

template <class T>
bool cell<T>::isOcuppied() {
    return s == ocuppied;
}

template <class T>
bool cell<T>::isDeleted() {
    return s == deleted;
}