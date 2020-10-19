
  MAKEFILE

    make all -- build all project
    make clean -- remove from main folder object files and tmp file from
                  test_output folder
    make test -- launch testing
    make help -- print README.md file

1. DESCRIPTION

This class allows user to parse string using methods which could be redefined
during program execution. Parser can detect two types of tokens integers and
strings (integers must be non-negative and must fit in uint64_t type).

All detected tokens will be processed by DigitalCallback and StringCallback.

All user-defined methods take argument of (void *) type, this is neccessary to
give an opportunity to use different classes in Parser (it could be containers
or other different objects defined by user).

    This class contains methods:
        help-methods:
            1) void SetStartCallback(std::function<void(void *)>)
            2) void SetFinishCallback(std::function<void(void *)>)
            3) void SetDigitTokenCallback(std::function<void(uint64_t, void *)>)
            4) void SetStringTokenCallback(std::function<void(std::string, void *)>)

        main-method:
            5) void Parse (std::string, void *)

            The string is a string for parsing.

        user-defined methods:
            6) void StartCallback(void *)            (public)
            7) void FinishCallback(void *)           (public)
            8) void DigitCallback(uint64_t, void *)  (private)
            9) void StringCallback(uint64_t, void *) (private)

            (Actually these members of Parser are not functions. They are only
             elements of function<...> type, which do nothing before
             redefinition. But user can use them as class methods)

2. HOW TO CREATE USER-DEFINED FUNCTIONS

    All user-defined functions have argument with type (void *), these arguments
    have to be casted to pointer on type which will be used by user.

    After creation of function user must call one of help-methods
    with name of created function as an argument.

    Sample: (for StartCallback):

        class Counter {
            public:
                int stringTokens;
                int intTokens;
                Counter() : strintTokens(-1), intTokens(-1) {}
        };

        void userStartCallbackFunction(void *a) {
            auto b = static_cast<Counter *>(a);
        /// after this operation we can work with b as an pointer to Counter
            b->stringTokens = 10;
            b->intTokens = 10;
            std::cout << "Your Counter get new parameters:\n";
            std::cout << "stringToken == " << b->stringTokens << "\n";
            std::cout << "intToken == " << b->intTokens << "\n";
        }

3. WARNINGS

    If in given string two tokens (integer and string) are concatenated then
program will be crashed with exit(1) and warning (in cerr)
    "Wrong format of parsed string
     Space expected between tokens"

4. TESTING

    All test samples are in tests folder, all test outputs are in test_output
    folder. To add new test you should watch at output format in file main.cpp.
    Correctness of test working is checking string by string in both files
    test_output/tmp and test_output/[filename].
