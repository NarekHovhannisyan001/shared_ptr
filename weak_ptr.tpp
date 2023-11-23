#ifndef WEAK_T
#define WEAK_T


template <class T>
Weak_ptr<T>::Weak_ptr(const Shared_ptr<T>& obj) : control_block(obj.getBlock()),m_ptr(obj.get())  {
    control_block->incrementWeak();
}

template <class T>
Weak_ptr<T>::~Weak_ptr() {
    if (control_block) {
        control_block->decrementWeak();
    }
}




template <class T>
bool Weak_ptr<T>::expired() const {
    return control_block == nullptr || control_block->use_count() == 0;
}

template <class T>
size_t Weak_ptr<T>::use_count() const {
    return control_block->use_count();
}

template <class T>
Shared_ptr<T> Weak_ptr<T>::lock() const {
    if (expired()) {
            return Shared_ptr<T>((T*)nullptr);
        } else {
            (control_block->use_count())++;
            return Shared_ptr<T>((T*)control_block);
        }
}


#endif //WEAK_T