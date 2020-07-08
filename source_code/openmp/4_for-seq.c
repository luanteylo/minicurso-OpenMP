#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


void inicializa(int **v, int size) {
  (*v) = (int *) malloc(sizeof(int)*size);
  for (int i = 0; i < size; i++) {
    (*v)[i] = rand() % 10000;
  }
}

float square(int x){
  int k = 0;
  while(k < 5000) k++;  // espera ocupada 
  return sqrt(x);  
}


int main(int argc, char **argv) {
	srand(time(NULL));
	
	int *vetor;
	int size = 1000000;

	inicializa(&vetor, size);
	  
	for(int i = 0; i < size; i++){
	  vetor[i] = square(vetor[i]);
	}
	  

	return 0;
}
