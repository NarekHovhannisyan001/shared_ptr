#ifndef CONTROLBLOCK_H
#define CONTROLBLOCK_H


#include <iostream>

template <class T>
class ControlBlock {

public:
    ControlBlock(T* ptr);
    ControlBlock(const ControlBlock& obj);
    ControlBlock(ControlBlock&& obj) noexcept;
    ~ControlBlock();

public:
    ControlBlock& operator=(const ControlBlock& obj);
    ControlBlock& operator=(ControlBlock&& obj) noexcept;
    void incrementStrong();
    void decrementStrong();
    void incrementWeak();
    void decrementWeak(); 
    const T* get() const;
    T* get();
    const size_t& use_count() const;
    size_t& use_count();
    const size_t& weak_count() const;
    size_t& weak_count();


private:
    T* m_ptr;
    std::size_t m_strongRefCount;
    std::size_t m_weakRefCount;
};

#include "controlBlock.tpp"

#endif //CONTROLBLOCK_H