/*
 * sigaction_2.c
	programma che gestisce più segnali
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler_sigint (int sig){
	printf("ricevuto segnale %d di interruzione \n", sig);
	return;
	}
	
	void handler_sigusr (int sig){
		printf("ricevuto segnale sigusr %d\n", sig);
		return;
		}
		

int main(int argc, char **argv)
{
	struct sigaction act_int, act_usr;
	
	act_int.sa_handler = handler_sigint;
	sigemptyset(&act_int.sa_mask);
	act_int.sa_flags =0;
	
	sigaction(SIGINT, &act_int, NULL);	// gestisce SIGINT
	
	act_usr.sa_handler = handler_sigusr;
	sigemptyset(&act_usr.sa_mask);
	act_usr.sa_flags =0;
	
	sigaction(SIGUSR1, &act_usr, NULL);	// gestisce SIGUSR1
	
	while (1){
		printf("ciao\n");
		sleep(1);
	}
	
	return 0;
}

