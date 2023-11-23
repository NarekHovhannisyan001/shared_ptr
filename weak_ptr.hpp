#ifndef VEC_H
#define VEC_H

#include "shared_ptr.hpp"


template <class T>
class Weak_ptr {

public:
    explicit Weak_ptr(const Shared_ptr<T>& obj);
    ~Weak_ptr();

public:
    Shared_ptr<T> lock() const;
    bool expired() const;
    size_t use_count() const;

private:
    ControlBlock<T>* control_block;
    T* m_ptr;

};



#include "weak_ptr.tpp"

#endif //VEC_H