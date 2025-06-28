#include <Rcpp.h>

#include "backend/distance_matrix.hpp"
#include "backend/init.hpp"

using namespace Rcpp;

/**
 * 
 *  AN EXAMPLE OF AN RCPP FUNCTION.
 *  
 *  Rcpp functions are functions that do have defined input/output Rcpp-Types.
 * 
 * NOTE: Normally Rcpp functions are auto-wrapped by Rcpp::compileAttributes() in an RcppExports.cpp,
 *  but since we want to maximize platform-independence and some systems get an
 *  enterRNGScope error in RcppExports.o when using [[Rcpp::export]] we wrap the functions manually.
 * 
 */
NumericMatrix cl_distance_matrix(const NumericMatrix& mat) {
    IntegerVector dim = mat.attr("dim");
    int rows = dim[0], cols = dim[1];

    std::vector<double> input(mat.begin(), mat.end());
    std::vector<double> output(rows * rows, 0);

    backend::distance_matrix(input.data(), rows, cols, output.data());

    NumericMatrix outmat(rows, rows);
    std::copy(output.begin(), output.end(), outmat.begin());

    return outmat;
}


/**
 * 
 *  SEXP WRAPPER SECTION.
 * 
 *  SEXP wrappers are functions whose sole purpose is redirection of inputs and outputs to and from Rcpp functions.
 * 
 */
extern "C" SEXP CLDistanceMatrix(SEXP matSEXP) {
    Rcpp::NumericMatrix mat(matSEXP);
    NumericMatrix out = cl_distance_matrix(mat);
    return Rcpp::wrap(out);
}

/**
 * 
 *  INIT SETTER.
 * 
 *  This function takes a special place as it sets the static linkage path to the resources for C to access them.
 *  Expand this function to whatever you need to pass to the dll/so on loading.
 * 
 */
extern "C" SEXP SetKernelsPath(SEXP kernelsPathSEXP) {
    std::string path = as<std::string>(kernelsPathSEXP);
    backend::set_kernels_path(path);
    return R_NilValue;
}


/**
 * 
 *  INIT SECTION.
 * 
 *  When wrapping your functions via SEXP manually you have to explicitly tell Rcpp how
 *  many SEXP arguments your wrapper functions have and register them under an export name.
 * 
 */
static const R_CallMethodDef CallEntries[] = {
    {"CLDistanceMatrix", (DL_FUNC) &CLDistanceMatrix, 1},
    {"SetKernelsPath", (DL_FUNC) &SetKernelsPath, 1},
    {NULL, NULL, 0}
};

extern "C" void R_init_DistanceMatrix(DllInfo* dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
