/* signal_fork.c

° un processo padre P0 genera N figli PN;
° il padre, per 10 volte: genera un num <r1> casuale tra 1 e 2, genera un num <r2> casuale tra 1 e N, invia il segnale sigusr<r1> al figlio P<r2>, sleep(2);
° il padre invia Sigkill a tutti i figli e termina;
° ogni figlio in loop infinito: attende l'arrivo di SIGUSR1 o SIGUSR2 e quando li riceve stampa il proprio PID + sig ricevuto;
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#define N 3
#define M 10


void sig_handler (int signum);


int main(void){
pid_t pid[N];
int r1, r2;
struct sigaction sa;

   for (int i=0; i<N; i++){
    pid[i] = fork();
    switch(pid[i]){
        case -1:
            perror("errore fork\n");
        exit(EXIT_FAILURE);

        case 0:
             sa.sa_flags = 0;
             sa.sa_handler = sig_handler;
             sigemptyset(&(sa.sa_mask));
             sigaction (SIGUSR1, &sa, NULL);
             sigaction (SIGUSR2, &sa, NULL);
            while(1) pause();
        break;

        default:
        break;
    }   // fine switch
   }    // fine for
    
    for (int i=0; i<M; i++){
        r1 = rand() % 2 + 1;
        r2 = rand() % N + 1;

        if(r1 == 1){
            if (kill(pid[r2-1], SIGUSR1) != 0) printf("errore kill\n");
        } else {
            if (kill(pid[r2-1], SIGUSR2) != 0) {
                printf("errore kill\n");
             }
            }
            sleep(2);
        }
        for (int i=0; i<N; i++){
            if(kill(pid[i], SIGKILL) != 0) printf("errore kill\n");
            }

    for (int i=0; i<N; i++){
        wait(NULL);
    }
    exit(EXIT_SUCCESS);
}


void sig_handler (int signum){
    if(signum == SIGUSR1){
    printf("ricevuto segnale SIGUSR1\n");
        } else if(signum == SIGUSR2){
        printf("ricevuto segnale SIGUSR2\n");
         }
    return;
}