
#include <stdio.h>


static void geo_handle_cuda_error(cudaError_t err, const char* file, int line) {
  if (err != cudaSuccess) {
    printf("%s in file: %s at line: %d\n", cudaGetErrorString(err), file, line);
    exit(EXIT_FAILURE);
  }
}

#define GEO_HANDLE_CUDA_ERROR( err ) (geo_handle_cuda_error(err, __FILE__, __LINE__))


int main() {
  cudaDeviceProp dev_properties;
  float minimum_cc = 6.0;
  GEO_HANDLE_CUDA_ERROR(cudaGetDeviceProperties(&dev_properties, 0));
  float cc = dev_properties.major + ( dev_properties.minor/10.0f );
  if ( cc < minimum_cc ) { 
    printf("Minimum Compute Capability of %2.1f required: %2.1f found. Not Building CUDA Code.\n",
            min_cc, cc);
    return 1;   //fail
  } else {
    printf("-arch=sm%d%d", dev_properties.major, dev_properties.minor);
    return 0; //cudaSUCCESS
  }

}
