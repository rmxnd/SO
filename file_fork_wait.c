#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int main (){
    pid_t pid[2];
    int status, fd, var_pid1, var_pid2;
    char da_scrivere1[]="HELLO", da_scrivere2[]="CIAO";

    if (fd = open("file_fork_wait.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) == -1){
        perror("errore fork\n");
        exit(EXIT_SUCCESS);
            }

    for (int i=1; i<=2; i++){
        switch(pid[i] = fork()){
            case -1:
                perror("error fork\n");
                close (fd);
                exit(EXIT_FAILURE);

            case 0: // figlio
                if (i==1){  // figlio 1
                    var_pid1=getpid();
                    for(int j=0; j<5; j++){
                    if(write(fd, da_scrivere1, sizeof(da_scrivere1)+1) == -1){
                        perror("errore write figlio 1\n");
                        exit(EXIT_FAILURE);
                            }
                            sleep(1);
                            }
                     } else if (i==2){   // figlio 2
                        var_pid2=getpid();
                         for(int j=0; j<5; j++){
                        if(write(fd, da_scrivere2, sizeof(da_scrivere2)+1) == -1){
                            perror("errore write figlio 2\n");
                            exit(EXIT_FAILURE);
                            }
                         sleep(1);
                         }
                        
                         }
                close(fd);
                exit(EXIT_SUCCESS);
        
            default:
                break;
            }
    }
    // padre
    if (close(fd)== -1){
        perror ("errore close\n");
        exit(EXIT_FAILURE);
            }
    if (waitpid(var_pid1, &status, 0) == -1){
        perror ("errore waitpid1\n");
        exit(EXIT_FAILURE);
        }
        if(WIFEXITED(status)){
            printf("[Padre] figlio %d terminato con stato %d\n", var_pid1, WEXITSTATUS(status));
        }   else {printf("figlio 1 terminato in modo anomalon");
                    }
     if (waitpid(var_pid2, &status, 0) == -1){
        perror ("errore waitpid2\n");
        exit(EXIT_FAILURE);
        }
        if(WIFEXITED(status)){
            printf("[Padre] figlio %d terminato con stato %d\n", var_pid2, WEXITSTATUS(status));
        }   else {printf("figlio 2 terminato in modo anomalon");
                    }
    
    exit(EXIT_SUCCESS);
}