
MAKE OPTIONS:

    make test (make all) - build main file (executable file)
    make clean - clear folder from *.o files
    make help - get README.md file


VECTOR:

    operator[]
    push_back
    pop_back
    emplace_back
    empty
    size
    clear
    begin, rbegin
    end, rend
    resize
    reserve
    capacity

VECTOR ITERATOR:

    unary *
    ++
    --
    <
    >
    <=
    >=
    ==
    !=
    += (int64_t or VectorIterator)
    -= (int64_t or VectorIterator)
    = (lvalue VectorIterator)

VECTOR REVERSE ITERATOR:

    unary *
    ++
    --
    <
    >
    <=
    >=
    ==
    !=
    += (int64_t or VectorIterator)
    -= (int64_t or VectorIterator)
    = (lvalue VectorIterator)

VECTOR ALLOCATOR:

    RESIZE = 2
    realloc

EXCEPTIONS (VectorException):

    - Wrong Index -- index is out of range
    - Vector is empty
    - Different Containers' iterator
    - Wrong size parameter
