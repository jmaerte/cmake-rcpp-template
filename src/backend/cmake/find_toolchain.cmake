######################################################################
#
#   CMake script to retrieve the C, CXX Compilers and MAKE from Rcpp.
#
#   This ensures:
#       1. That the C backend and the Rcpp library are both built
#           using the same toolchain.
#       2. That the toolchain is actually complete and found as Rcpp
#           and Rtools is installed.
#
######################################################################

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