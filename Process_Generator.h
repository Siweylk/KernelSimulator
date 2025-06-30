#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


#ifndef PROCESS_GENERATOR_H
#define PROCESS_GENERATOR_H

extern struct sincro s;
extern struct process_queue pq;
extern struct process_queue *array_colas;

void* generar_proceso(void *args){
    int num_core = 0;
    while(1){
        pthread_mutex_lock(&s.mutextimers);
        pthread_cond_wait(&s.condpg, &s.mutextimers);

        if(array_colas[num_core].ocupacion != 50){
            struct PCB proceso = {rand() % 10000, rand() % 50};
            array_colas[num_core].procesos[array_colas[num_core].ocupacion] = proceso;
            array_colas[num_core].ocupacion++;
            printf("Se activa el PG y se ñade proceso al core %i\n", num_core);
        }
        else{
            printf("La cola esta llena, no se generara proceso este ciclo \n");
        }

        if(num_core != s.cores-1){
            num_core++;
        }
        else{
            num_core=0;
        }
        pthread_mutex_unlock(&s.mutextimers);
    }
    return 0;
}

#endif