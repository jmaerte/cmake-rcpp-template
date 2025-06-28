#include <Rcpp.h>
#include "backend/distance_matrix.hpp"
#include "backend/init.hpp"

using namespace Rcpp;

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


extern "C" SEXP CLDistanceMatrix(SEXP matSEXP) {
    Rcpp::NumericMatrix mat(matSEXP);
    NumericMatrix out = cl_distance_matrix(mat);
    return Rcpp::wrap(out);
}

extern "C" SEXP SetKernelsPath(SEXP kernelsPathSEXP) {
    std::string path = as<std::string>(kernelsPathSEXP);
    backend::set_kernels_path(path);
    return R_NilValue;
}

static const R_CallMethodDef CallEntries[] = {
    {"CLDistanceMatrix", (DL_FUNC) &CLDistanceMatrix, 1},
    {"SetKernelsPath", (DL_FUNC) &SetKernelsPath, 1},
    {NULL, NULL, 0}
};

extern "C" void R_init_DistanceMatrix(DllInfo* dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
