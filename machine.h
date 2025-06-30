#ifndef MACHINE_C
#define MACHINE_C

struct sincro{
    int tic;
    int tocPG;
    int tocSchDis;
    int frec;
    int timerPG;
    int timerSchDis;
    int done;
    int cores;

    pthread_mutex_t mutex;
    pthread_cond_t cond1;
    pthread_cond_t cond2;

    pthread_mutex_t mutextimers;
    pthread_cond_t condsch;
    pthread_cond_t condpg;
};

struct PCB{
    int pid;
    int vida;
};

struct process_queue{
    struct PCB procesos[50];
    int ocupacion;
    int cantejec;
    int proejec;

    int quantum;
};


#endif