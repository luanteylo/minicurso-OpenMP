#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>


void inicializa(int **v, int size) {
  (*v) = (int *) malloc(sizeof(int)*size);
  for (int i = 0; i < size; i++) {
    (*v)[i] = rand() % 10000;
  }
}

float square(int x){
  int k = 0;
  while(k < 5000) k++;
  return sqrt(x);  
}


int main(int argc, char **argv) {
	srand(time(NULL));
	
	int *vetor;
	int size = 1000000;
	
	
	inicializa(&vetor, size);
	
	#pragma omp parallel
	{
		// divisão do trabalho
		int local_init, local_end, chunk;
		chunk = size / omp_get_num_threads();
		local_init = omp_get_thread_num() * chunk;
		local_end = (omp_get_thread_num()+1) * chunk;
		if ((omp_get_num_threads()-1) == omp_get_thread_num()) local_end = size;
		
		// calculo, cada thread responsável por seu bloco de memória
		for (int i = local_init; i < local_end; i++) {
			vetor[i] = square(vetor[i]);
		} 
	}
	  

	return 0;
}
