#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#include "Clock.h"
#include "timer.h"
#include "Process_Generator.h"
#include "sch_disp.h"
#include "machine.h"


struct sincro s;
struct process_queue pq;
struct process_queue *array_colas;


/*int** createArrays(int numArrays) {

    struct PCB** arrays = (struct PCB**)malloc(numArrays * sizeof(struct PCB*));

    // Check if memory allocation was successful
    if (arrays == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1); // Exit with an error code
    }

    // Allocate memory for each individual one-dimensional array
    for (int i = 0; i < numArrays; ++i) {
        arrays[i] = (struct PCB*)malloc(20 * sizeof(struct PCB));
    }
}*/



int main(int argc, char *argv[]){
    
    //Definicion de variables del KERNEL
    int frec, timerPG, timerSchDis, cores;
    printf (" Cual será la frecuencia del sistema         --> ");
    scanf  ("%d", &frec);
    printf (" Cada cuanto se activara el Process Generator  --> ");
    scanf  ("%d", &timerPG);
    printf (" Cada cuanto se activara el Scheduler/Dispatcher  --> ");
    scanf  ("%d", &timerSchDis);
    printf (" Cuantos cores tendrá el sistema         --> ");
    scanf  ("%d", &cores);

    //Inicializacion de variables de sincronizacion
    
    s.cores = cores;
    s.tic = 1;
    s.tocSchDis = 0;
    s.tocPG = 0;
    s.frec = frec;
    s.timerPG = timerPG;
    s.timerSchDis = timerSchDis;

    //Crear array de colas
    array_colas = malloc(s.cores * sizeof(struct process_queue));

    //Inicializar quantum en cada cola
    for(int i = 0; i < s.cores; i++){
        array_colas[i].quantum = 25;
    }


    
    pq.ocupacion = 0;

    printf("Frecuencia: %i\n", s.frec);
    pthread_t clock;
    pthread_t timer;
    pthread_t process_generator;
    pthread_t SchDis;
    pthread_create(&clock, NULL, Clock, NULL);
    pthread_create(&timer, NULL, Timer_PG, NULL);
    pthread_create(&timer, NULL, Timer_SchDis, NULL);
    pthread_create(&process_generator, NULL, generar_proceso, NULL);
    pthread_create(&SchDis, NULL, administrarProcesos, NULL);

    pthread_join(clock, NULL);
}