#ifndef CONTROLBLOCK_T
#define CONTROLBLOCK_T

template <class T>
ControlBlock<T>::ControlBlock( T* ptr) : m_ptr(ptr), m_strongRefCount(1),m_weakRefCount(0) {}

template <class T>
ControlBlock<T>::ControlBlock(const ControlBlock& obj) 
    : m_ptr(obj.m_ptr), m_strongRefCount(obj.m_strongRefCount), m_weakRefCount(obj.m_weakRefCount) {
    incrementStrong();
}

template <class T>
ControlBlock<T>::ControlBlock(ControlBlock&& obj) noexcept 
    : m_ptr(obj.m_ptr), m_strongRefCount(obj.m_strongRefCount), m_weakRefCount(obj.m_weakRefCount) {
    obj.m_ptr = nullptr;
    obj.m_strongRefCount = 0;
    obj.m_weakRefCount = 0;
}



template <class T>
ControlBlock<T>::~ControlBlock() {
    delete m_ptr;
}

template <class T>
void ControlBlock<T>::incrementStrong() {
    ++m_strongRefCount;
}

template <class T>
void ControlBlock<T>::decrementStrong() {
    if (m_strongRefCount > 0) {
        --m_strongRefCount;
        if (m_strongRefCount == 0) {
            delete m_ptr;
            m_ptr = nullptr;
        }
    }
}

template <class T>
void ControlBlock<T>::incrementWeak() {
    ++m_weakRefCount;
}

template <class T>
void ControlBlock<T>::decrementWeak() {
    if (m_weakRefCount > 0) {
        --m_weakRefCount;
    }
}


template <class T>
const T* ControlBlock<T>::get() const  {
    return m_ptr;
}

template <class T>
T* ControlBlock<T>::get() {
    return m_ptr;
}





template <class T>
const std::size_t& ControlBlock<T>::use_count() const {
    return m_strongRefCount;
}

template <class T>
std::size_t& ControlBlock<T>::use_count() {
    return m_strongRefCount;
}



template <class T>
const std::size_t& ControlBlock<T>::weak_count() const {
    return m_weakRefCount;
}

template <class T>
std::size_t& ControlBlock<T>::weak_count() {
    return m_weakRefCount;
}

template <class T>
ControlBlock<T>& ControlBlock<T>::operator=(const ControlBlock<T>& obj) {
    if (this != &obj) {
        decrementStrong();
        m_ptr = obj.m_ptr;
        m_strongRefCount = obj.m_strongRefCount;
        m_weakRefCount = obj.m_weakRefCount;
        incrementStrong();
    }
    return *this;
}

template <class T>
ControlBlock<T>& ControlBlock<T>::operator=(ControlBlock<T>&& other) noexcept {
    if (this != &other) {
        decrementStrong();
        m_ptr = other.m_ptr;
        m_strongRefCount = other.m_strongRefCount;
        m_weakRefCount = other.m_weakRefCount;
        other.m_ptr = nullptr;
        other.m_strongRefCount = 0;
        other.m_weakRefCount = 0;
    }
    return *this;
}




#endif //CONTROLBLOCK_T