#pragma once


template <class T, class U>
class Hash_Collisions {
  private:
    class cell {
      public:
        T key;
        U value;
        bool isEmpty = true;
        cell<T,U>* next = nullptr;
    };
    cell<T,U> *p;
    int max_size;
    int collision_size; // 14 to 21 % of max_size
    int (*hash_function)(int,T);
  public:
    Hash_Collisions(int,int (*)(int,T));
    ~Hash_Collisions();
    void add(T,U);
    void del(T,U);
    bool isIn(T);
};


template <class T, class U>
Hash_Collisions<T,U>::Hash_Collisions(int n,int (*f)(int,T)) {
    collision_size = n * 0.14;
    max_size = n - collision_size;
    hash_function = f;
    p = new cell<T,U>[max_size + collision_size];
}

template <class T, class U>
Hash_Collisions<T,U>::~Hash_Collisions() {
    delete[] p;
}

template <class T, class U>
void Hash_Collisions<T,U>::add(T key,U value) {
    if (isIn(key)) {
        return;
    }
    int base_idx = hash_function(key);
    if (p[base_idx].isEmpty) {
        p[base_idx].isEmpty = false;
        p[base_idx].key = key;
        p[base_idx].value = value;
    }
    else {
        cell<T,U> *q = p + base_idx;
        while (q->next != nullptr) {
            q = q->next;
        }
        for (cell<T,U> *r = p + max_size + 1; r != p + max_size + collision_size + 1; r++) {
            if (r->isEmpty) {
                r->isEmpty = false;
                r->key = key;
                r->value = value;
                q->next = r;
                break;
            }
        }
    }
}

template <class T, class U>
void Hash_Collisions<T,U>::del(T key, U value) {
    // ToDo
}

template <class T, class U>
bool Hash_Collisions<T,U>::isIn(T key) {
    int base_idx = hash_function(key);
    if (!p[base_idx].isEmpty) {
        cell<T,U> *q = p + base_idx;
        while (q != nullptr) {
            if (q->key == key) {
                return true;
            }
            q = q->next;
        }
    }
    return false;
}