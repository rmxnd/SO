/*
 * segnali_prove.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>


void stampa_messaggio (void);
void handler (int sig);
void handler_2 (int sig);
void handler_padre (int sig);
void handler_figlio (int sig);


int main(int argc, char **argv)
{
	int scelta;
	pid_t pid;
	
	menu:
	printf ("MENU\n\n1: cattura SIGINT\n2: suicida\n3: snooze\n4: crea figlio e gestisci i segnali in modo diverso\n");
	scanf("%d", &scelta);
	
	switch(scelta){
		case 1:
		signal(SIGINT, handler); //registro funzione handler per SIGINT (=CTRL+C)
		stampa_messaggio();
		break;
		
		case 2:
		kill(getpid(), SIGINT);
		break;
		
		case 3:
		signal(SIGINT, handler_2);
		stampa_messaggio();
		break;
		
		case 4:
		pid = fork();
		
		if (pid == 0){	// figlio
			signal(SIGINT, handler_figlio);
		} else if (pid == -1) {
		perror("fork fallita\n");
		}
		else {	// padre
			signal(SIGINT, handler_padre);
		}
		
		break;
		
		default:
		printf("scelta non consentita\n\n\n");
		goto menu;
	}	// fine switch
	
	return 0;
}


void stampa_messaggio (void){
	while (1){
		puts("ciao\n");
		sleep(1);
		}
		
	return;
	}

void handler (int sig){
	printf("ricevuto segnale %d\n", sig);
	return;
	}

void handler_2 (int sig){
	printf("ricevuto segnale %d\ndormo per 3 secondi...\n", sig);
	sleep(3);
	return;
	}
	
	void handler_padre (int sig){
		printf ("segnale ricevuto dal padre = %d\n", sig);
		return;
		}

void handler_figlio (int sig){
	printf ("segnale ricevuto dal figlio = %d\n", sig);
	return;
	}
