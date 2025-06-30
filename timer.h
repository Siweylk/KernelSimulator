#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#ifndef TIMER_H
#define TIMER_H

extern struct sincro s;

void* Timer_PG(void *args){
    pthread_mutex_lock(&s.mutex);
    while(1){
        if(s.tic % s.timerPG == 0){
            pthread_cond_signal(&s.condpg);
        }
        pthread_cond_signal(&s.cond1);
        s.done++;
        pthread_cond_wait(&s.cond2, &s.mutex);
    }
    pthread_mutex_unlock(&s.mutex);
}


void* Timer_SchDis(void *args){
    pthread_mutex_lock(&s.mutex);
    while(1){
        if(s.tic % s.timerSchDis == 0){
            pthread_cond_signal(&s.condsch);
        }
        pthread_cond_signal(&s.cond2);
        s.done++;
        pthread_cond_wait(&s.cond1, &s.mutex);
    }
    pthread_mutex_unlock(&s.mutex);
}


#endif
