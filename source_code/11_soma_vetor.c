#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void inicializa(int **v, int size) {
    (*v) = (int *) malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++) {
        (*v)[i] = 1;
    }
}

int main(int argc, char **argv) {

    int *vetor;
    int size = 1000000;

    inicializa(&vetor, size);

    unsigned long acc = 0;

    //#pragma omp parallel for
    for (int i = 0; i < size; i++) {
        acc += vetor[i];
    }

    printf("Resultado: %lu\n", acc);

    return 0;
}
