__kernel void distance_matrix(
    __global double* output,
    __global double* input,
    const int N,
    const int DIM){

  size_t i = get_global_id(0);
  size_t j = get_global_id(1);

  if(i < N && j < i){
    double tmpRes = 0;
    for(int k = 0; k < DIM; ++k){
      double diff = input[i + k*N] - input[j + k*N];
      tmpRes += diff * diff;
    }
    tmpRes = sqrt(tmpRes);
    output[j * N + i] = tmpRes;
    output[i * N + j] = tmpRes;
  }
}