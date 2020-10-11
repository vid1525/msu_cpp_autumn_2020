#include <cstdint>
#include <algorithm>

class Allocator {
public:
    void makeAllocator(const uint64_t maxSize) {
        allocPtr = new char[maxSize];
    }

    char *alloc(const uint64_t size) {
        if (offset + size <= allocSize) {
            uint64_t ptr = offset;
            offset += size;
            return allocPtr + ptr;
        }
        return nullptr;
    }

    void reset() {
        offset = 0;
    }

    Allocator() : allocSize(0), offset(0), allocPtr(nullptr) {}

    ~Allocator() {
        delete [] allocPtr;
    }
private:
    uint64_t allocSize;
    uint64_t offset;
    char *allocPtr;
};
