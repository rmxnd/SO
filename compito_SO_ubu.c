#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>


#define FIGLI 6
#define LOOP 4
void *handler (int sig);


int main () {
    pid_t pid[FIGLI];
    struct sigaction act;

    for(int i=0; i<FIGLI; i++){
        switch (pid[i] = fork()) {
            case -1:
                perrror("errorre fork figlio %d\n", i+1);
                exit(EXIT_FAILURE);

            case 0: //figlio
                act.sa_handler = handler(SIGUSR1);
                act.sa_handler = handler(SIGUSR2);
                act.sa_flags = 0;
                if(sigemptyset(&(act.sa_mask)) == -1){
                    perror("errore sigemptyset");
                    exit(EXIT_FAILURE);
                }

                if(sigaction(SIGUSR1, &act, NULL) == -1) {
                    perror("errore sigaction1\n");
                    exit(EXIT_FAILURE);
                }
                if(sigaction(SIGUSR2, &act, NULL) == -1) {
                    perror("errore sigaction2\n");
                    exit(EXIT_FAILURE);
                }
            default:
                break;
        }
        printf("[PADRE] figlio %d creato\n", i+1);
    }

    for (int i=0; i<FIGLI; i++){
        for (int j=0; j<LOOP; j++){
            if (kill(pid[i], SIGUSR1) == -1){
                perror("[PADRE] errore kill\n figlio %d loop %d\n", i+1, j+1);
                EXIT(EXIT_FAILURE);
            }
            if (kill(pid[i], SIGUSR2) == -1){
                perror("[PADRE] errore kill\n figlio %d loop %d\n", i+1, j+1);
                EXIT(EXIT_FAILURE);
            }
        }
    }

    for (int i=0; i<FIGLI; i++){
        if(wait(NULL) == -1){
            perror("errore wait\n");
            exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_SUCCESS);
}


void *handler (int sig){
    static int r;

    if (sig == SIGUSR1){
        r = rand()%LOOP+1;
        printf("[FIGLIO] ricevuto SIGUSR1, generato %d\n", r);
    } else if (sig == SIGUSR2) {
        printf("[FIGLIO] ricevuto SIGUSR2, generato %d\n", r);
    }

    return NULL;
}