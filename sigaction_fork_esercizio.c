#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


#define N 3
void handler(int signal);
void figlio (int num);


int main () {
    pid_t pid;
    int var_pid;
    struct sigaction sact;

    sact.sa_handler = handler;
    sigemptyset(&(sact.sa_mask));
    sact.sa_flags = 0;
    if(sigaction(SIGUSR1, &sact, NULL) == -1){
        perror("errore sigaction\n");
        exit(EXIT_FAILURE);
    }


    for (int i=0; i<N; i++){
        pid = fork();
        switch(pid){
            case -1:
                perror("errore fork\n");
                exit(EXIT_FAILURE);

            case 0: // figlio
                figlio(N-i);
                exit(EXIT_SUCCESS);

            default:
                break;
        }
        var_pid = pid;
    }   // fine for
    // padre
    sleep(1);
    if(kill(var_pid, SIGUSR1) == -1){
        perror("errore invio kill, funzione figlio\n");
        exit(EXIT_FAILURE);
    }
    printf("[padre] attesa segnale...\n");
    fflush(stdout);
    pause();

    exit(EXIT_SUCCESS);
}


void figlio (int num){
    printf("[Figlio: %d] PID: %u\t attesa segnale...\n", num, getpid());
    fflush(stdout);
    pause();
    if(kill(var_pid, SIGUSR1) == -1){
        perror("errore invio kill, funzione figlio\n");
        exit(EXIT_FAILURE);
    }
}


void handler(int signal){
    if(signal == SIGUSR1){
        printf("PID: %u\t arrivato SIGUSR1\n", getpid());
    } else printf("errore segnale SIGUSR1 NON ricevuto\n");
}