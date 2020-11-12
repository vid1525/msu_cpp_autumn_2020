
MAKE OPTIONS:

    make test (make all) - build main file (executable file)
    make clean - clear folder from *.o files
    make help - get README.md file


SERIALIZER INTERFACE:

    Error save(T &value) -- takes one element of user's class
    Error operator() (Args&&...args) -- takes different count of elements
        of different types

DESERIALIZER INTERFACE:

    Error operator()(Args&&... args) -- takes different count of elements
    Error load(T &value) -- takes one element of user's class

USER CLASS REQUIREMENTS:

    User class must contain special method:
        template <typename Serializer>
        Error serialize(Serializer &serializer) {
            return serializer(...) /// in place of ... user must write down his class attributes
        }

RETURNING VALUE:

    All functions return NoError if all is ok otherwise CorruptedArchive;

    All possible returning values are in enum Error.

TEST MODE:

    1.
    All tests are contained in test folder.
    To add new test file you should create test file,
    add this file in test folder and add filename to testfile_list.txt.

    During testing will be created new file (tmp file) in folder test_output.
    Result of work of  will be written in tmp and then content from tmp
    will be compared with necessary file in test_output folder.

    TEST INPUT- AND OUTPUT- FILES SHOULD HAVE SAME NAMES.

    For better understanding of test process see more information in main.cpp and test samples in test and test_output folders.
