#include "Process_Generator.h"
#include "machine.h"

#ifndef SCh_DISP_H
#define SCh_DISP_H

extern struct process_queue pq;
extern struct sincro s;

void * administrarProcesos(){
    while(1){
        pthread_mutex_lock(&s.mutextimers);
        pthread_cond_wait(&s.condsch, &s.mutextimers);

        //Por cada core
        for(int j = 0; j < s.cores; j++){
            if(array_colas[j].ocupacion < 25){
                array_colas[j].quantum = 25;
            }
            else{
                array_colas[j].quantum = 10;
            }


            for(int i = array_colas[j].ocupacion-1; i>=0; i--){
                if(array_colas[j].procesos[i].vida > 0) break;
                printf("El ultimo tiene vida\n");
                array_colas[j].ocupacion--;
            }

            for(int i=0; i < array_colas[j].ocupacion; i++){
                if(array_colas[j].procesos[i].vida <= 0){
                    printf("Se ha eliminado un proceso\n");
                    if(i == array_colas[i].ocupacion){
                        pq.ocupacion--;
                    }
                    else{
                        array_colas[j].procesos[i] = array_colas[i].procesos[array_colas[i].ocupacion-1];
                        array_colas[j].ocupacion--;
                    }
                }
                //printf("Proceso %i, vida: %i\n", i, array_colas[i].procesos[i].vida);
            }
            //printf("Numero total de procesos cuando se llama al Sch: %i\n", array_colas[j].ocupacion);

        }
        pthread_mutex_unlock(&s.mutextimers);
    }
    return 0;
}

#endif