#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>


#define N 5 // n° figli
void *sig_handler (int sig);


int main () {
    int status;
    pid_t pid[N];
    struct sigaction act;

 act.sa_handler = sig_handler;
            act.sa_flags=0;
            if(sigemptyset((sigset_t *)&(act.sa_mask)) == -1){
                perror("errore sigemptyset\n");
                exit(EXIT_FAILURE);
            }
            if(sigaction(SIGUSR1, &act, NULL) == -1){
                perror("[FIGLIO]\terrore sigaction\n");
                exit(EXIT_FAILURE);
            }
            if(sigaction(SIGQUIT, &act, NULL) == -1){
                perror("[FIGLIO]\terrore sigaction\n");
                exit(EXIT_FAILURE);
            }

    for (int i=0; i<N; i++){    // padre genera 5 figli
       switch(pid[i] = fork()) {
        case -1:
            perror("errore fork\n");
            exit(EXIT_FAILURE);

        case 0:
           
            while(1) pause();
            exit(EXIT_SUCCESS);

        default:
            break;
        }
    }

    // padre manda x5 volte ad ogni figlio SIGUSR1
    for (int i=0; i<N; i++){    // ad ogni figlio
        for (int j=0; j<N; j++){    // x5 volte
            if(kill(pid[i], SIGUSR1) == -1){
                perror("[PADRE]\terrore invio kill\n");
                exit(EXIT_FAILURE);
            }
            sleep(1);
        }
    }

    // padre manda SIGQUIT ad ogni figlio e attende la terminazione
    for (int i=0; i<N; i++){
        if(kill(pid[i], SIGQUIT) == -1){
            perror("[PADRE]\terrore invio kill\n");
            exit(EXIT_FAILURE);
        }
    }
    for (int i=0; i<N; i++){
       if(waitpid(pid[i], &status, 0) == -1){
            perror("[PADRE]\terrore invio waitpid\n");
            exit(EXIT_FAILURE);
       }
    }
    printf("[PADRE]\tFINE\n");
    exit(EXIT_SUCCESS);
}


void *sig_handler (int sig){
    if(sig == SIGQUIT) pause();
    else if (sig == SIGUSR1 && (getpid()%2) == 0 ) printf ("[FIGLIO]\t PID: %d Pari\n", getpid());
    else if (sig == SIGUSR1 && (getpid()%2) != 0 ) printf ("[FIGLIO]\t PID: %d Dispari\n", getpid());
    return NULL;
}