//deepptr.cpp
#include "deepptr.h"
#include "pasticceria.h"

void DeepPtr::increaseRef()
{
    if (p != nullptr)
        p->references++;
}

DeepPtr::DeepPtr(Pasticceria *ptr) : p(ptr) {
    increaseRef();
}

DeepPtr::DeepPtr(const DeepPtr & d) : p( d.p) {
    increaseRef();
}

DeepPtr &DeepPtr::operator =(const DeepPtr &obj) {
    p = obj.p;
    increaseRef();
    return *this;
}

bool DeepPtr::operator ==(const DeepPtr &obj) {
    return this == &obj || p == obj.p ||
            ( p != nullptr && p->equals(obj.p));
}

Pasticceria *DeepPtr::data() const {
    return p;
}

DeepPtr::~DeepPtr()
{
    if (p != nullptr)
    {
        p->references--;
        if (p -> references <= 0)
            delete p;
    }
}
