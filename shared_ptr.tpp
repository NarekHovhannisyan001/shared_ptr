#ifndef SHARED_T
#define SHARED_T

template <class T>
Shared_ptr<T>::Shared_ptr(const Shared_ptr<T>& obj) : control_block(obj.control_block){
    control_block->incrementStrong();
}


template <class T>
Shared_ptr<T>::Shared_ptr(Shared_ptr<T>&& obj) noexcept : control_block(nullptr) {
   std::swap(control_block,obj.control_block);
}


template <class T>
Shared_ptr<T>::Shared_ptr(const T& obj) : control_block(new ControlBlock<T>(obj)) {}

template <class T>
Shared_ptr<T>::Shared_ptr(T* ptr) : control_block(new ControlBlock<T>(ptr)) {}

template <class T>
Shared_ptr<T>::~Shared_ptr() {
    if (control_block) {
        control_block->decrementStrong();
    }
}

template <class T>
Shared_ptr<T>::Shared_ptr( const ControlBlock<T>* controlBlock)
    : control_block(controlBlock) {
    if (control_block) {
        control_block->incrementStrong();
    }
}



template <class T>
Shared_ptr<T>& Shared_ptr<T>::operator=(const Shared_ptr<T>& obj) {
    if (this != &obj) {
        if (control_block) {
            control_block->decrementStrong();
        }
        control_block = obj.control_block;
        if (control_block) {
            control_block->incrementStrong();
        }
    }
    return *this;
}


template <class T>
Shared_ptr<T>& Shared_ptr<T>::operator=(Shared_ptr<T>&& obj) noexcept {
    if (this != &obj) {
        control_block->decrementStrong();
        control_block->get() = obj.control_block->get();
        control_block->use_count() = obj.control_block->use_count();
        obj.control_block->get() = nullptr;
        obj.control_block->use_count() = 0;
    }
    return *this;
}


template <class T>
T& Shared_ptr<T>::operator*() const {
    return *control_block->get();
}

template <class T>
ControlBlock<T>* Shared_ptr<T>::getBlock() const {
    return control_block;
}


template <class T>
T* Shared_ptr<T>::operator->() const {
    return control_block->get();
}

template <class T>
void Shared_ptr<T>::swap(Shared_ptr& obj) {
    // std::swap(*(control_block->get()), *obj.control_block->get());
    // std::swap(control_block->use_count(), obj.control_block->use_count());
    std::swap(control_block, obj.control_block);
}


template <class T>
void Shared_ptr<T>::reset() {
    if (control_block) {
        control_block->decrementStrong();
    }
}


template <class T>
void Shared_ptr<T>::reset(T* newPtr) {
    if (control_block) {
        control_block->decrementStrong();
    }

    if (newPtr) {
        control_block = new ControlBlock<T>(newPtr);
    } else {
        control_block = nullptr;
    }
}



template <class T>
T* Shared_ptr<T>::get() const {
    return control_block->get();
}

template <class T>
size_t Shared_ptr<T>::use_count() const {
    return control_block->use_count();
}

template <class T>
bool Shared_ptr<T>::unique() const {
    return control_block->use_count() == 1;
}

#endif //SHARED_T