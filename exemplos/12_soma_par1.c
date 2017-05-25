#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void inicializa(unsigned long **v, int size) {
	(*v) = (unsigned long *) malloc(sizeof(unsigned long)*size);

	for (int i = 0; i < size; i++) {
		(*v)[i] = 1;
	}
}

int main(int argc, char **argv) {
	
	unsigned long *vetor;
	int size = 1000000;

	inicializa(&vetor, size);
	
	unsigned long acc = 0;
	
	unsigned long *local_acc;
	
	#pragma omp parallel
	{
	    #pragma omp single
	    {
	        local_acc = (unsigned long *) malloc(sizeof(unsigned long) * omp_get_num_threads());
	    }

	    // divisão do trabalho
	    int local_init, local_end, chunk;
	    chunk = size / omp_get_num_threads();
	    local_init = omp_get_thread_num() * chunk;
	    local_end = (omp_get_thread_num()+1) * chunk;
	    if ((omp_get_num_threads()-1) == omp_get_thread_num()) local_end = size;
	    
	    local_acc[omp_get_thread_num()] = 0;

	    // soma sem race condition, cada thread em sua posição de memória
	    for (int i = local_init; i < local_end; i++) {
		    local_acc[omp_get_thread_num()] += vetor[i];
	    } 

	    // sincronização, garantia de que todas as threads terminaram suas tarefas
	    #pragma omp barrier

	    // redução a um só valor
	    #pragma omp single 
	    {
		    for (int i = 0; i < omp_get_num_threads(); i++) {
			    acc += local_acc[i];
		    }	
	    }
	}

	printf("Resultado: %lu\n",acc);

	return 0;
}
