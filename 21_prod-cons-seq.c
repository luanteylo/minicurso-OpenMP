#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

int produce() {
        sleep(1); // em segundos, aparentemente
        return rand() % 1000;
}

void consume(int *queue, int i){
        sleep(rand() % 5);
        printf("consumiu %d\n", queue[i]);
}

void inicializa(int **v, int size) {
  (*v) = (int *) malloc(sizeof(int)*size);
  for (int i = 0; i < size; i++) {
    (*v)[i] = produce();
        printf("produziu %d\n", (*v)[i]);
  }
}

int main(int argc, char **argv) {
    srand(time(NULL));
    int *vetor;
    int size = atoi(argv[1]);
    inicializa(&vetor, size);
    int i = 0;
    while(i < size){
        consume(vetor, i);
        i++;
    }
    return 0;
}