/*
 * prova_sigaction.c
 stampa un messaggio ad ogni SIGINT ricevuto
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler (int sig){	// funzione di gestione del segnale
	printf("segnale interruzione %d ricevuto\n", sig);
	}

struct sigaction act;


int main(int argc, char **argv)
{
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);	// inizializza una mask di segnali vuota
	act.sa_flags=0;	// nessun flag
	
	sigaction(SIGINT, &act, 0); // cattura CTRL+C
	
	while (1){
		printf("ciao\n");
		sleep(1);
	}
	
	
	return 0;
}

