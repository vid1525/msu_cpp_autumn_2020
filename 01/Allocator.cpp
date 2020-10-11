#include <cstdint>
#include "Allocator.h"

void Allocator::makeAllocator(const uint64_t maxSize) {
    delete [] allocPtr;
    allocPtr = new char[maxSize];
    allocSize = maxSize;
    offset = 0;
}

char *Allocator::alloc(const uint64_t size) {
    if (offset + size <= allocSize) {
        uint64_t ptr = offset;
        offset += size;
        return allocPtr + ptr;
    }
    return nullptr;
}

void Allocator::reset() {
    offset = 0;
}

Allocator::Allocator() : allocSize(0), offset(0), allocPtr(nullptr) {}

Allocator::~Allocator() {
    delete [] allocPtr;
}
