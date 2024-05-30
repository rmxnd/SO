#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>


void sig_handler (int sig);


int main () {
    pid_t F1, F2;
    int r, status;
    struct sigaction sact;


    sact.sa_handler = sig_handler;
    sigemptyset(&sact.sa_mask);
    sact.sa_flags = 0;

    F1 = fork();
    switch (F1) {
        case -1:
            perror("errore fork");
            exit(EXIT_FAILURE);

        case 0: // figlio
            F2 = fork();
            switch (F2) {
                case -1:
                    perror("errore fork");
                    exit(EXIT_FAILURE);

                case 0: // figlio del figlio
                    alarm(8);
                    exit(EXIT_SUCCESS);

                default:
                 break;
             }  // fine F2

                r = rand()%1+10;
                if ( r > 5) {
                    if (sigaction (SIGUSR1, &sact, NULL) == -1){
                        perror("errore sigaction in F1\n");
                        exit(EXIT_FAILURE);
                    }
                    if (kill(F2, SIGUSR1) == -1){
                        perror("errore kill in F1\n");
                        exit(EXIT_FAILURE);
                    }
                }
                if (waitpid (F2, NULL, 0) == -1){
                    perror("errore waitpid in F1\n");
                    exit(EXIT_FAILURE);
                }
                if (WEXITSTATUS(status)){
                    printf("[FIGLIO F1] figlio F2 terminato normalmente\n");
                    exit(WEXITSTATUS(status));
                } else exit(EXIT_FAILURE);

        default:
            break;
    }   // fine F1

     if (waitpid (F1, NULL, 0) == -1){
        perror("errore waitpid padre\n");
        exit(EXIT_FAILURE);
        }
    if (WIFEXITED(status)){
        printf("[PADRE] figlio F1 terminato normalmente con stato %d\n", WEXITSTATUS(status));
    } else {
        perror("errore WIFEXITED padre\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}


void sig_handler (int sig){
    if(sig == SIGUSR1){
        printf("ricevuto segnale SIGUSR1\n");
        alarm(0);
        exit(EXIT_SUCCESS);
    } else if (sig == SIGALRM)
    return;
}