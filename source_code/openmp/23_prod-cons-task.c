#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

int produce() {
        sleep(1); // em segundos, aparentemente
        int i = rand() % 1000;
         printf("produziu %d\n",i);
        return i;
}

void consume(int *queue, int i){
        sleep(rand() % 5);
        printf("consumiu %d\n", queue[i]);
}

int main(int argc, char **argv) {
    srand(time(NULL));
    int size = atoi(argv[1]);
    int queue_size = 15;
    int *vetor = (int *) malloc(sizeof(int)*size);;
    int prod_pos = 0;
    int cons_pos = 0;
    int produced = 0;
    int consumed = 0;
	
	#pragma omp parallel
	{
		#pragma omp for nowait
		for (int i = 0; i < size; i++){
			#pragma omp task
			{
				int idx;
				#pragma omp critical
				{
					while(consumed >= produced) sleep(1); // consumo depende de produção disponível
					idx = cons_pos;
					cons_pos++;
					consumed++;
				}
				consume(vetor, idx % queue_size);
			}
		}
		
		#pragma omp master
		{
			int i = 0;
			
			while (i < size){
				if (prod_pos >= cons_pos % queue_size){ //produção depende de espaço disponível
					vetor[prod_pos] = produce();
					produced++;
					prod_pos++;
					if (prod_pos == queue_size)
						prod_pos = 0;
					i++;
				} else {
					sleep(1);
				}
			}
		}
	}
	
    return 0;
}