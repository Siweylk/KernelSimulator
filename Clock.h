#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "machine.h"


#ifndef CLOCK_H
#define CLOCK_H

extern struct sincro s;
extern struct process_queue pq;
extern struct process_queue *array_colas;



void* Clock(void *args){

    int tenp_konp = 1;
    double dormir_tmp = (1.0/s.frec)*1000000;
    printf("Frecuencia: %f\n", dormir_tmp);


    //Empieza a contar

    pthread_mutex_lock(&s.mutex);
    while (1){
        usleep(dormir_tmp);
        s.tic++;
        printf("El valor del tic: %i\n", s.tic);
        fflush(stdout);


        //Esperar que los dos timers cuenten

        while(s.done < tenp_konp){
            pthread_cond_wait(&s.cond2, &s.mutex);
        }
        s.done=0;
        //EJECUTAR PROCESOS

        //Por cada core
        for(int i = 0; i < s.cores; i++){
            //Si hay procesos en su cola
            if(array_colas[i].ocupacion != 0){
                //Si sigue siendo su turno
                if(array_colas[i].cantejec <= array_colas[i].quantum){
                    array_colas[i].procesos[array_colas[i].proejec].vida--; 
                    array_colas[i].cantejec++;
                    printf("Se le ha quitado vida al proceso %i en el core %i\n", array_colas[i].proejec, i);
                }
                //Si hay que pasar al siguiente proceso
                else{
                    array_colas[i].proejec++;
                    if(array_colas[i].proejec == array_colas[i].ocupacion) array_colas[i].proejec = 0;
                    array_colas[i].cantejec = 0;
                }
            }
        }

        if( s.tic == 500){
            for(int i = 0; i < s.cores; i++){
                printf("Core %i, ocupacion: %i\n", i, array_colas[i].ocupacion);
                for(int j =0; j<array_colas[i].ocupacion; j++){
                    printf("Proceso %i, vida restante: %i\n", j, array_colas[i].procesos[j].vida);
                    fflush(stdout);
                }
            }
        }
        pthread_cond_broadcast(&s.cond2);
        
        
        
        

        /*if(pq.ocupacion != 0){
            if(cantejec <= s.quantum){
                pq.procesos[proejec].vida--;
                cantejec++;

            }else{
                proejec++;
                if(proejec == pq.ocupacion) proejec = 0;
                cantejec = 0;
            }
        }*/
        //printf("La vida del proceso %i es: %i\n", proejec, pq.procesos[proejec].vida);
    }
    pthread_mutex_unlock(&s.mutex);
}


#endif