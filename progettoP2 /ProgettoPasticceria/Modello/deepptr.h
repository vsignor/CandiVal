//deepptr.h
#ifndef DEEPPTR_H
#define DEEPPTR_H

#include <iostream>

class Pasticceria;

class DeepPtr
{
private:
    Pasticceria* p;
    void increaseRef();
public:
    DeepPtr(Pasticceria* = nullptr); // costruttore
    DeepPtr(const DeepPtr&); // costruttore di copia
    DeepPtr& operator=(const DeepPtr&); // assegnazione
    bool operator==(const DeepPtr&); // uguaglianza
    Pasticceria* data() const;
    ~DeepPtr(); // distruzione

};

#endif // DEEPPTR_H
