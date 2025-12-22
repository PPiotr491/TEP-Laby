#ifndef TEP_SMARTPOINTER_H
#define TEP_SMARTPOINTER_H

template <typename T>
class SmartPointer {
    // ============== RefCounter class ============== //
    class RefCounter {
        public:
            RefCounter();
            int increment();
            int decrement();
            int getCounter() const;
        private:
            int i_count;
    };

// ============== SmartPointer class ============== //
public:
    SmartPointer(T *pointer);
    SmartPointer(const SmartPointer &other);

    ~SmartPointer();

    T& operator*();
    T* operator->();

    SmartPointer& operator=(const SmartPointer &other);

private:
    void clearPointer();
    void copyPointer(const SmartPointer<T> &other);

    RefCounter *counter;
    T *pointer;

};

#endif //TEP_SMARTPOINTER_H