#ifndef ALLOCATOR_H
#define ALLOCATOR_H

class Allocator {
public:
    void makeAllocator(const uint64_t maxSize);
    char *alloc(const uint64_t size);
    void reset();
    Allocator();
    ~Allocator();
private:
    uint64_t allocSize;
    uint64_t offset;
    char *allocPtr;
};

#endif
