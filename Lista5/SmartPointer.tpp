#ifndef SMARTPOINTER_TPP
#define SMARTPOINTER_TPP

#include <cstddef>

#include "SmartPointer.h"
class EquationTree;
// ============== RefCounter class ============== //
template<typename T>
SmartPointer<T>::RefCounter::RefCounter() {
    i_count = 0;
}

template<typename T>
int SmartPointer<T>::RefCounter::increment() {
    return ++i_count;
}

template<typename T>
int SmartPointer<T>::RefCounter::decrement() {
    return --i_count;
}

template<typename T>
int SmartPointer<T>::RefCounter::getCounter() const {
    return i_count;
}


// ============== SmartPointer class ============== //
template<typename T>
SmartPointer<T>::SmartPointer(T *pointer) {
    this->pointer = pointer;

    counter = new RefCounter();
    counter->increment();
}

template<typename T>
SmartPointer<T>::SmartPointer(const SmartPointer<T> &other) {
    copyPointer(other);
}

template<typename T>
SmartPointer<T>::~SmartPointer() {
    clearPointer();
}

template<typename T>
T& SmartPointer<T>::operator*() {
    return *pointer;
}

template<typename T>
T* SmartPointer<T>::operator->() {
    return pointer;
}

template<typename T>
SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer &other) {
    if (this == &other) {
        return *this;
    }

    if (this->pointer != NULL) {
        clearPointer();
    }

    copyPointer(other);

    return *this;
}

template<typename T>
void SmartPointer<T>::clearPointer() {
    if (counter->decrement() == 0) {
        delete pointer;
        delete counter;
    }
}

template<typename T>
void SmartPointer<T>::copyPointer(const SmartPointer<T> &other) {
    pointer = other.pointer;
    counter = other.counter;
    counter->increment();
}

#endif // SMARTPOINTER_TPP
