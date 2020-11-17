
MAKE OPTIONS:

    make test (make all) - build main file (executable file)
    make clean - clear folder from *.o files
    make help - get README.md file


FORMAT INTERFACE:

    std::string format(const std::string &format, Args...) -- takes format string
        and different count of arguments

EXCEPTIONS (FormatException):

    - No closing bracket in the end -- if format string is "...{..." without any "}"
    - Doubled open bracket {index} -- if format string is "...{...{...", between { { no }
    - Invalid argument index: [i..j] -- if argument is wrong
    - Index out of range index -- if argument is out of range of given format parameters
    - Invalid } index = {index} -- if format string "...}..." before } there are right bracket
                                   sequence before }

RETURNING VALUE:

    Formatted string if no exceptions were thrown.
