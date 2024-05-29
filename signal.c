/*
 * signal.c
  SIGINT = processo interrotto dall'utente ---> codice = 2
 */


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>


void func (int sig){
	printf("ricevuto segnale %d\n", sig);
	signal(SIGINT, func);
	}

void func_2 (int sig){	// = CTRL+C
	printf("ricevuto segnale %d\n", sig);
	signal(SIGQUIT, func_2);
	}
	
	void func_3 (int sig){	// = CTRL+C
	printf("ricevuto segnale %d\n", sig);
	signal(SIGTSTP, func_3);
	}

int main(int argc, char **argv)
{
	signal(SIGINT, func);	// imposta il signal handler (gestore del segnale)
	signal(SIGQUIT, func_2);
	signal(SIGTSTP, func_3);
	
	while(1) {	// sempre
	puts("ciao\n");
	sleep(1);
	}
	
	return 0;
}

