//container.h
#pragma once
#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>
#include <string>
using std::cerr;
using std::endl;

template <class T>
class Container
{
    friend class iterator;
    friend class const_iterator;
private:
    class Nodo
    {
    public:
        T info;
        Nodo* next;
        Nodo* prev;
        Nodo(const T& i=T(), Nodo* n=nullptr, Nodo* p=nullptr) : info(i),next(n), prev(p) {}
        Nodo(const Nodo& n) : info(n.info),next(n.next),prev(n.prev) {}
        ~Nodo() {
            if (next != nullptr)
                delete next;
        }
    };

    Nodo *first, *last;
    int dim;
    void copia(Nodo *primo);
public:
    Container();
    Container(const Container & c);
    Container& operator=(const Container& c);
    ~Container();
    T& operator[](int) const;
    Container<T>& operator+=(const Container<T>& c);
    T get(int);
    void insert(const T&);
    Container<T> search(const T&) const;
    void remove(const T&);
    T *primo() const;
    T *ultimo() const;
    int size() const;
    T& push_back(const T& i);

    class iterator
    {
        public:
            Nodo* p;
            iterator();
            iterator& operator++();
            iterator operator ++(int) const;
            iterator& operator--();
            iterator operator--(int) const;
            T& operator*() const;
            T* operator->() const;
            bool operator!=(const iterator&) const;
            bool operator==(const iterator&) const;

        };

    class const_iterator
    {
    public:
        Nodo* p;
        const_iterator();
        const_iterator& operator++();
        const_iterator operator++(int) const;
        const_iterator& operator--();
        const_iterator operator--(int) const;
        const T& operator*() const;
        const T* operator->() const;
        bool operator!=(const const_iterator&) const;
        bool operator==(const const_iterator&) const;

    };


    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
};

#endif // CONTAINER_H

template <class T>
Container<T>::Container() : first(nullptr), last(nullptr), dim(0) {}

template <class T>
Container<T>::Container(const Container<T> &c) : first(nullptr), last(nullptr), dim(c.dim) {
    copia(c.first);
}

template <class T>
Container<T> &Container<T>::operator=(const Container<T> &c) {
    if (this != &c) {
        if (first)
            delete first;
        first = nullptr;
        last = nullptr;
        copia(c.first);
        dim = c.dim;
    }
    return *this;
}

template <class T>
Container<T>::~Container() {
    if (first) {
        delete first;
    }
}

template <class T>
void Container<T>::copia(Nodo *primo) {
    if (primo) {
        first = last = new Nodo(primo -> info);
        while (primo -> next) {
            primo = primo -> next;
            last -> next =  new Nodo(primo -> info, nullptr, last);
            last = last -> next;
        }
    }
}

template <class T>
T & Container<T>::operator[](int i) const {

    if (i>=dim)
        throw std::string("indice fuori bound");

    Nodo* temp= first;
    bool esci =false;
    for (int j=0; j<dim && !esci; ++j) {
        if (j == i)
            esci = true;
        else
            temp = temp -> next;
    }

    return (temp -> info);
}
template <class T>
Container<T> & Container<T>::operator+=(const Container<T>& c) {

    if(first == last==nullptr){
        copia(c.first);
    } else{
        Nodo* primo = c.first;
        if (primo) {
            last = new Nodo(primo -> info);
            while (primo -> next) {
                primo = primo -> next;
                last -> next =  new Nodo(primo -> info, nullptr, last);
                last = last -> next;
            }
        }
    }
    return this;
}
template <class T>
T *Container<T>::primo() const {
    return &(first -> info) ;
}

template <class T>
T *Container<T>::ultimo() const {
    return &(last -> info);
}

template <class T>
int Container<T>::size() const {
    return dim;
}
template <class T>
Container<T> Container<T>:: search(const T& obj) const {
    Container<T> c;
    Nodo* temp= first;
    for (int j=0; j<dim; ++j) {
        if (temp -> info == obj)
            c.push_back(temp -> info);
        temp = temp -> next;
    }
    return c;
}
template <class T>
void Container<T>:: remove(const T& obj) {
    Container<T> c;
    Nodo* temp= first;
    Nodo* prec= nullptr;
    while (temp != nullptr) {
        if (temp-> info == obj) {
            if(prec == nullptr) {
                first = first -> next;
                temp -> next = nullptr;
                delete temp;
                temp = first;
            }
            else {
                prec -> next = temp -> next;
                temp -> next = nullptr;
                delete temp;
                temp = prec->next;

            }
        }
        else {
            prec = temp;
            temp = temp -> next;
        }
    }
}

template <class T>
T &Container<T>::push_back(const T &i) {
    if(!first)
        first = last = new Nodo(i);
    else {
        last -> next = new Nodo(i, nullptr, last);
        last = last -> next;
    }
    ++dim;
    return last -> info;

}

template <class T>
typename Container<T>::iterator Container<T>::begin() {
    iterator temp;
    temp.p = first;
    return temp;
}

template <class T>
typename Container<T>::iterator Container<T>::end() {
    iterator temp;
    return temp;
}

template <class T>
typename Container<T>::const_iterator Container<T>::begin() const {
    const_iterator temp;
    temp.p = first;
    return temp;
}

template <class T>
typename Container<T>::const_iterator Container<T>::end() const {
    const_iterator temp;
    return temp;
}

template <class T>
Container<T>::iterator::iterator() : p(nullptr) {}
template <class T>
typename Container<T>::iterator & Container<T>::iterator::operator++() {
    if (p)
        p = p -> next;
    return *this;
}

template <class T>
typename Container<T>::iterator Container<T>::iterator::operator++(int) const {
    iterator temp;
    if (p){
        temp.p = p;
        p = p -> next;
    }
    return temp;
}

template <class T>
typename Container<T>::iterator & Container<T>::iterator::operator--() {
    if (p)
        p = p -> prev;
    return *this;
}

template <class T>
typename Container<T>::iterator Container<T>::iterator::operator--(int) const {
    iterator temp;
    if (p) {
        temp.p = p;
        p = p -> prev;
    }
    return temp;
}

template <class T>
T & Container<T>::iterator::operator*() const {
    return p -> info;
}

template <class T>
T* Container<T>::iterator::operator->() const {
    return &(p -> info);
}

template <class T>
bool Container<T>::iterator::operator!=(const iterator& i) const {
    return !(p == i.p);
}

template <class T>
bool Container<T>::iterator::operator==(const iterator& i) const {
    return p == i.p;
}

template <class T>
Container<T>::const_iterator::const_iterator() : p(nullptr) {}
template <class T>
typename Container<T>::const_iterator & Container<T>::const_iterator::operator++() {
    if (p)
        p = p -> next;
    return *this;
}

template <class T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator++(int) const {
    const_iterator temp;
    if (p){
        temp.p = p;
        p = p -> next;
    }
    return temp;
}

template <class T>
typename Container<T>::const_iterator & Container<T>::const_iterator::operator--() {
    if (p)
        p = p -> prev;
    return *this;
}

template <class T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator--(int) const {
    const_iterator temp;
    if (p) {
        temp.p = p;
        p = p -> prev;
    }
    return temp;

}

template <class T>
const T & Container<T>::const_iterator::operator*() const {
    return p -> info;
}

template <class T>
const T* Container<T>::const_iterator::operator->() const {
    return &(p -> info);
}

template <class T>
bool Container<T>::const_iterator::operator!=(const const_iterator& i) const {
    return !(p == i.p);
}

template <class T>
bool Container<T>::const_iterator::operator==(const const_iterator& i) const {
    return p == i.p;
}
