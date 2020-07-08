// Condicional compilation Facility

#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv) {
    int thread_num = 0;
    printf("Hello World :)\n");
    
    #pragma omp parallel 
    {
      #if _OPENMP
	     thread_num = omp_get_thread_num();
      #endif

      printf("Hello World from thread %d\n",thread_num);
      printf("E agora??? %d\n", thread_num);
   }
      
   
   return 0;
}
