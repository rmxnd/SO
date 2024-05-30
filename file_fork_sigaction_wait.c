#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>


#define CHILD_NUM 10
int fd = 0;
void sig_handler (int sig);


int main () {
    pid_t pid[CHILD_NUM];
    struct sigaction sact;
    int status;

    
    sact.sa_handler = sig_handler;
    if (sigemptyset(&(sact.sa_mask)) == -1){
        perror("errore sigemptyset\n");
        exit(EXIT_FAILURE);
        }
    sact.sa_flags = 0;

    if ((fd = open("file_fork_sigaction_wait.txt", O_CREAT | O_WRONLY, S_IWUSR | S_IRUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) == -1) {
        perror("errore open\n");
        exit(EXIT_FAILURE);
        }

    for (int i=0; i<CHILD_NUM; i++){
        pid[i]=fork();

        switch (pid[i]){
            case -1:
                perror("errore fork\n");
                exit(EXIT_FAILURE);
            
            case 0:
                if(sigaction(SIGUSR1, &sact, NULL) == -1){
                    perror("errore sigaction1\n");
                    exit(EXIT_FAILURE);
                         }
                sigaction(SIGKILL, &sact, NULL); // non faccio il controllo perche mi da errore
                while(1) pause();
                exit(EXIT_SUCCESS);
            default:
                break;
        }
    }

    for (int i=0; i<5; i++){
        for (int j=0; j<CHILD_NUM; j++){
            if (kill(pid[j], SIGUSR1) == -1){
                perror("errore kill1\n");
                exit(EXIT_FAILURE);
            }
        }
        sleep(1);
    }
    for (int i=0; i<CHILD_NUM; i++){
        if (kill(pid[i], SIGKILL) == -1){
            perror("errore kill2\n");
            exit(EXIT_FAILURE);
        }
    }
    for (int i=0; i<CHILD_NUM; i++){
          if (waitpid(pid[i], &status, 0) == -1){
            perror("errore waitpid\n");
            exit(EXIT_FAILURE);
        }
    }
    close (fd);
    exit(EXIT_SUCCESS);
}


void sig_handler (int sig){
  if (sig == SIGUSR1) {
    char buf[50];

    printf("arrivo di un segnale...\n");
    sprintf(buf, "PID: %d\t PPID: %d\n", getpid(), getppid());
    if ( write(fd, buf, strlen(buf)) == -1){
        perror("errore write\n");
            exit(EXIT_FAILURE);
    }
        }
}