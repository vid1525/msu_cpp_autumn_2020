#ifndef VECTOR_H
#define VECTOR_H

#include <cstdlib>
#include <exception>
#include <string>

class VectorException : public std::exception {
private:
    std::string errorType;
public:
    VectorException(const std::string &errorMsg) : errorType(errorMsg) {}

    const char *what() const noexcept override {
        return errorType.c_str();
    }
};

template <typename T>
class VectorAllocator {
public:
    void realloc(const int64_t Size, const int64_t newSize, int64_t &Allocated, T *&Array) {
        if (newSize > Allocated) {
            if (Allocated == 0 || newSize / Allocated >= RESIZE) {
                Allocated = newSize;
            } else {
                Allocated *= RESIZE;
            }
            T *newArray = new T[Allocated];
            copy(newArray, Array, Size);
            delete [] Array;
            Array = newArray;
        }
    }

private:
    const int64_t RESIZE = 2;

    void copy(T *dest, const T *source, const int64_t len) const {
        for (int64_t i = 0; i < len; ++i) {
            dest[i] = source[i];
        }
    }
};

template <typename T, typename Value>
class VectorIterator {
public:
    VectorIterator(T &a, const int64_t index)
      : Index(index)
      , Link(a) {}

    Value& operator *() {
        return Link[Index];
    }

    void operator ++() {
        if (Index < Link.size()) {
            ++Index;
        }
    }

    void operator --() {
        if (Index - 1 >= 0) {
            --Index;
        }
    }

    VectorIterator<T, Value>& operator +=(const int64_t value) {
        Index += value;
        return *this;
    }

    VectorIterator<T, Value>& operator -=(const int64_t value) {
        Index -= value;
        return *this;
    }

    VectorIterator<T, Value>& operator +=(const VectorIterator &value) {
        Index += value.Index;
        return *this;
    }

    VectorIterator<T, Value>& operator -=(const VectorIterator &value) {
        Index -= value.Index;
        return *this;
    }

    bool operator == (const VectorIterator<T, Value> &iter) const {
        return &Link == &iter.Link && Index == iter.Index;
    }

    bool operator != (const VectorIterator<T, Value> &iter) const {
        return !(*this == iter);
    }

    bool operator < (const VectorIterator<T, Value> &iter) const {
        if (&Link != &iter.Link) {
            throw VectorException("Different Containers' Iterators\n");
        }
        return Index < iter.Index;
    }

    bool operator <= (const VectorIterator<T, Value> &iter) const {
        return *this < iter || *this == iter;
    }

    bool operator > (const VectorIterator<T, Value> &iter) const {
        return !(*this < iter || *this == iter);
    }

    bool operator >= (const VectorIterator<T, Value> &iter) const {
        return *this > iter || *this == iter;
    }

    VectorIterator<T, Value>& operator =(VectorIterator &x) {
        Link = x.Link;
        Index = x.Index;
        return *this;
    }

private:
    mutable int64_t Index;
    T &Link;
};

template <typename T, typename Value>
class ReverseVectorIterator {
public:
    ReverseVectorIterator(T &a, const int64_t index)
      : Index(index)
      , Link(a) {}

    Value& operator *() {
        return Link[Index];
    }

    void operator ++() {
        if (Index >= 0) {
            --Index;
        }
    }

    void operator --() {
        if (Index < Link.size() - 1) {
            ++Index;
        }
    }

    ReverseVectorIterator<T, Value>& operator +=(const int64_t value) {
        Index -= value;
        return *this;
    }

    ReverseVectorIterator<T, Value>& operator -=(const int64_t value) {
        Index += value;
        return *this;
    }

    ReverseVectorIterator<T, Value>& operator +=(const ReverseVectorIterator &value) {
        Index -= value.Index;
        return *this;
    }

    ReverseVectorIterator<T, Value>& operator -=(const ReverseVectorIterator &value) {
        Index += value.Index;
        return *this;
    }

    bool operator == (const ReverseVectorIterator<T, Value> &iter) const {
        return &Link == &iter.Link && Index == iter.Index;
    }

    bool operator != (const ReverseVectorIterator<T, Value> &iter) const {
        return !(*this == iter);
    }

    bool operator > (const ReverseVectorIterator<T, Value> &iter) const {
        if (&Link != &iter.Link) {
            throw VectorException("Different Containers' Iterators\n");
        }
        return Index > iter.Index;
    }

    bool operator >= (const ReverseVectorIterator<T, Value> &iter) const {
        return *this > iter || *this == iter;
    }

    bool operator < (const ReverseVectorIterator<T, Value> &iter) const {
        return !(*this > iter || *this == iter);
    }

    bool operator <= (const ReverseVectorIterator<T, Value> &iter) const {
        return *this < iter || *this == iter;
    }

    ReverseVectorIterator<T, Value>& operator =(ReverseVectorIterator &x) {
        Link = x.Link;
        Index = x.Index;
        return *this;
    }

private:
    mutable int64_t Index;
    T &Link;
};

template <typename T, typename Allocator = VectorAllocator<T>>
class Vector {
public:
    Vector()
      : Allocated(0)
      , Size(0)
      , Array(nullptr) {}

    Vector(const int64_t size)
      : Allocated(size < 0 ? throw VectorException("\n") : size)
      , Size(size)
      , Array(new T[size]) {}

    Vector(const int64_t size, const T value)
      : Allocated(size < 0 ? throw VectorException("Wrong size parameter\n") : size)
      , Size(size)
      , Array(new T[size]) {
        std::fill(Array, Array + Size, value);
    }

    Vector(Vector &&vector)
      : Array(vector.Array)
      , Size(vector.Size)
      , Allocated(vector.Allocated){
        vector.Array = nullptr;
    }

    Vector(const Vector &vector) {
        Size = vector.Size;
        Allocated = vector.Allocated;
        Array = new T[Allocated];
        copy(Array, vector.Array, Size);
    }

    ~Vector() {
        delete [] Array;
    }

    T& operator [](const int64_t index) {
        if (index < 0 || index > Size) {
            throw VectorException("Wrong index\n");
        }
        return Array[index];
    }

    const T& operator [](const int64_t index) const {
        if (index < 0 || index > Size) {
            throw VectorException("Wrong index\n");
        }
        return Array[index];
    }

    int64_t size() const noexcept {
        return Size;
    }

    void clear() noexcept {
        Size = 0;
    }

    bool empty() const noexcept {
        return Size == 0;
    }

    void push_back(const T value) {
        Alloc.realloc(Size, Size + 1, Allocated, Array);
        Array[Size] = value;
        ++Size;
    }

    void pop_back() {
        if (empty()) {
            throw VectorException("Vector is empty\n");
        }
        --Size;
    }

    int64_t capacity() const noexcept {
        return Allocated;
    }

    void reserve(const int64_t newSize) {
        Alloc.realloc(Size, newSize, Allocated, Array);
    }

    template <typename... Args>
    void emplace_back(Args&&... args) {
        this->push_back(T(std::forward<Args>(args)...));
    }

    void resize(const int64_t newSize) {
        Alloc.realloc(Size, newSize, Allocated, Array);
        Size = newSize;
    }

    VectorIterator<Vector<T>, T> begin() noexcept {
        return VectorIterator<Vector<T>, T>(*this, 0);
    }

    VectorIterator<Vector<T>, T> end() noexcept {
        return VectorIterator<Vector<T>, T>(*this, this->Size);
    }

    ReverseVectorIterator<Vector<T>, T> rbegin() noexcept {
        return ReverseVectorIterator<Vector<T>, T>(*this, this->Size - 1);
    }

    ReverseVectorIterator<Vector<T>, T> rend() noexcept {
        return ReverseVectorIterator<Vector<T>, T>(*this, -1);
    }

private:
    int64_t Allocated;
    int64_t Size;
    T *Array;
    Allocator Alloc;

    void copy(T *dest, const T *source, const int64_t len) const {
        for (int64_t i = 0; i < len; ++i) {
            dest[i] = source[i];
        }
    }
};

#endif
