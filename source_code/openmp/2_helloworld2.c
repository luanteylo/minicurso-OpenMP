#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv) {
  printf("Hello World :)\n");
  #pragma omp parallel 
  {
    printf("Hello World from thread %d\n", omp_get_thread_num());
    printf("E agora??? %d\n", omp_get_thread_num());
  }
  return 0;
}
