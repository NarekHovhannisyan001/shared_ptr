#ifndef SHARED_H
#define SHARED_H

#include "controlBlock.hpp"

#include <iostream>


template <class T>
class Shared_ptr {

public:
    Shared_ptr(const Shared_ptr<T>& obj);
    Shared_ptr(Shared_ptr<T>&& obj) noexcept;
    Shared_ptr(const T& obj);
    Shared_ptr(T* ptr);
    Shared_ptr(const ControlBlock<T>* obj);
    ~Shared_ptr();


public:
    Shared_ptr<T>& operator=(const Shared_ptr<T>& obj);
    Shared_ptr<T>& operator=(Shared_ptr<T>&& obj) noexcept;
    T& operator*() const;
    T* operator->() const;
    void swap(Shared_ptr& obj);
    void reset();
    void reset(T* obj);
    T* get() const;
    ControlBlock<T>* getBlock() const;
    size_t use_count() const;
    bool unique() const;

private:
    ControlBlock<T>* control_block;

};



#include "shared_ptr.tpp"


#endif //SHARED_H