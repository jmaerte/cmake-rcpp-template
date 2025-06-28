execute_process (
    COMMAND R --slave -e "cat(Sys.which('g++'))"
    OUTPUT_VARIABLE CMAKE_CXX_COMPILER
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process (
    COMMAND R --slave -e "cat(Sys.which('gcc'))"
    OUTPUT_VARIABLE CMAKE_C_COMPILER
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process (
    COMMAND R --slave -e "cat(Sys.which('make'))"
    OUTPUT_VARIABLE CMAKE_MAKE_PROGRAM
    OUTPUT_STRIP_TRAILING_WHITESPACE
)