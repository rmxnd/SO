#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>


#define N_FIGLI 6
#define LOOP_PADRE 4
static int rand_num = 0;

void *sig_handler (int sig);


int main(int argc, char **argv)
{
	pid_t pid[N_FIGLI];
	struct sigaction act;

	for (int i=0; i<N_FIGLI; i++){
		pid[i] = fork();
		switch (pid[i]) {
			case -1:
				perror("errore fork\n");
				exit(EXIT_FAILURE);

			case 0:	//figlio
				printf("figlio %d creato correttamente\n", i+1);

				act.sa_handler = sig_handler(SIGUSR1);
				act.sa_handler = sig_handler(SIGUSR2);
				sigemptyset(&(act.sa_mask));
				act.sa_flags = 0;
				if (sigaction(SIGUSR1, &act, NULL) == -1) {
					perror("errore sigaction1 figlio\n");
					exit(EXIT_FAILURE);
				}

				if (sigaction(SIGUSR2, &act, NULL) == -1) {
					perror("errore sigaction2 figlio\n");
					exit(EXIT_FAILURE);
				}

                while (1) {
					pause();
					fflush(stdout);
				}
				exit(EXIT_SUCCESS);

			default:	//padre
				break;
		}
	}

	for(int i=0; i<N_FIGLI; i++){
	if(kill(pid[i], SIGUSR1) == -1) {
					perror("[PADRE] errore kill sigusr1\n");
					exit(EXIT_FAILURE);
						}
				sleep(2);
			}
	// padre manda x4 volte sigusr2 a ogni figlio
	for(int j=0; j<LOOP_PADRE; j++) {
					for(int i=0; i<N_FIGLI; i++){
						if(kill(pid[i], SIGUSR2) == -1) {
							perror("[PADRE] errore kill sigusr2\n");
							exit(EXIT_FAILURE);
						}
					}
					sleep(5);
				}

	for (int i=0; i<N_FIGLI; i++){
		wait(NULL);
	}
	exit(EXIT_SUCCESS);
}


void *sig_handler (int sig){
	srand(time(NULL));
	int tmp_rand_num = rand()%4+1;


	if (sig == SIGUSR1){
		fflush(stdout);
		printf("[FIGLIO] pid: %d, ricevuto sigusr1, numero generato: %d\n", getpid(), tmp_rand_num);
	} else if (sig == SIGUSR2) {
		fflush(stdout);
		rand_num += tmp_rand_num;
		printf("[FIGLIO] pid: %d, ricevuto sigusr2, numero random = %d, totale: %d\n", getpid(), tmp_rand_num, rand_num);

		sleep(rand_num);
	}
	return NULL;
	}