#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv) {
	// quantos numeros primos entre 1 e N ?
	
	unsigned long n = 99999;
	unsigned long aux = 2;

	unsigned long prime = 0;
	
	//Solução Feia. Por Força Bruta!
	
	for (unsigned long i = 2; i < n; i++) {
		
		while (aux < i) {
			if (i % aux == 0) break;
			aux++;
		}
		
		if (aux == i) prime++;

		aux = 2;
	}

	printf("%lu primos entre 1 e %lu\n",prime,n);

	return 0;
}
