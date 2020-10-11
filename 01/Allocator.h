#ifndef ALLOCATOR_H
#define ALLOCATOR_H

class Allocator {
public:
    void makeAllocator(const uint64_t maxSize);
    char *alloc(const uint64_t size);
    void reset();
    Allocator();
    ~Allocator();

protected:
    uint64_t allocSize;
    uint64_t offset;
    char *allocPtr;
};

class DebugAllocator : public Allocator {
public:
    uint64_t getOffset() {
        return offset;
    }

    uint64_t getAllocSize() {
        return allocSize;
    }
};

#endif
