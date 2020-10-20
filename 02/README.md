
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

All user-defined methods take argument of UserClass type, this is neccessary to
give an opportunity to use different classes in Parser (it could be containers
or other different objects defined by user).

    This class contains methods:
        help-methods:
            1) void SetStartCallback(std::function<void(UserClass &)>)
            2) void SetFinishCallback(std::function<void(UserClass &)>)
            3) void SetDigitTokenCallback(std::function<void(uint64_t, UserClass &)>)
            4) void SetStringTokenCallback(std::function<void(std::string, UserClass &)>)

        main-method:
            5) void Parse (std::string, UserClass &)

            The string is a string for parsing.

        user-defined methods:
            6) void StartCallback(UserClass &)            (public)
            7) void FinishCallback(UserClass &)           (public)
            8) void DigitCallback(uint64_t, UserClass &)  (private)
            9) void StringCallback(uint64_t, UserClass &) (private)

            (Actually these members of Parser are not functions. They are only
             elements of function<...> type, which do nothing before
             redefinition. But user can use them as class methods)

2. HOW TO CREATE USER-DEFINED FUNCTIONS

    All user-defined functions have argument with type UserClass &.

    After creation of function user must call one of help-methods
    with name of created function as an argument.

    Sample: (for StartCallback):

        class Counter {
            public:
                int stringTokens;
                int intTokens;
                Counter() : strintTokens(-1), intTokens(-1) {}
        };

        void userStartCallbackFunction(Counter &b) {
            b.stringTokens = 10;
            b.intTokens = 10;
            std::cout << "Your Counter get new parameters:\n";
            std::cout << "stringToken == " << b.stringTokens << "\n";
            std::cout << "intToken == " << b.intTokens << "\n";
        }

        int main() {  // maybe in other function
            ....
            Counter val;
            TokenParser<Counter> ps; /// parser creating
            ps.SetStartCallback(userStartCallbackFunction); /// set new start function
            ps.StartCallback(val); /// call startCallback
            ....
        }

3. TESTING

    All test samples are in tests folder, all test outputs are in test_output
    folder. To add new test you should watch at output format in file main.cpp.
    Correctness of test working is checking string by string in both files
    test_output/tmp and test_output/[filename].
