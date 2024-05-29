/*
 * signal_esercizio.c
 * 
 un processo padre genera N processi figli.
 il padre dopo avere creato i figli itera I volte eseguendo :
 -sleep di 2 secondi;
 -genera un numero casuale r1 tra 1 e 2;
 -genera un numero casuale r2 compreso tra 1 e N;
 - invia segnale SIGUSR<r1> al figlio PID<r2>.
 il padre uccide i figli con SIGKILL.
 * 
 ogni figlio fa un loop infinito:
 -attende l'arrivo di SIGUSR1 e SIGUSR2;
 -stampa il proprio PID e il segnale ricevuto.  
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>


#define N 20	// figli
#define I 10	// iterazioni


void child_sig_handler (int sig);


int main(int argc, char **argv){
	pid_t figlio[N];
	int i, r1, r2;
	struct sigaction sact;
	
	
	 for (i=0; i<N; i++){
		 figlio[i] = fork();
		 
		 switch (figlio[i]) {
			 case -1:
			 perror("fork fallita\n");
			 exit(1);
			 
			 
			 case 0:	// figlio
			 sigemptyset(&(sact.sa_mask));
			 sact.sa_flags = 0;
			 sact.sa_handler = child_sig_handler;
			 sigaction(SIGUSR1, &sact, NULL);
			 sigaction(SIGUSR2, &sact, NULL);
			 			 
				while(1){
				pause();
				}
			 break;
			 
			 default:
			 break;
		 }	// fine switch
	 }	// fine for
	 
	 /* padre */
	 srand(getpid());
	 for (i=0; i<I; i++){
		 sleep(1);
		 r1=(rand()%2)+1;
		 r2=rand()%N+1;
		 
		 if ( r1==1) {
			  if (kill(figlio[r2-1], SIGUSR1) != 0)
		 printf("errore kill\n");
		 } else {
			  if (kill(figlio[r2-1], SIGUSR2) != 0)
		 printf("errore kill\n");
		 }
	 }	// fine for
	 
	 for (i=0; i<N; i++){
		 if (kill(figlio[i], SIGKILL) != 0)
		 printf("errore kill\n");
	 }
	 
	return 0;
}


void child_sig_handler (int sig) {
	printf("figlio con PID = %d\nsegnale catturato %d\n", getpid(), sig);
	
	if (sig == SIGUSR1){
		printf("segnale ricevuto dal padre sigusr1 con pid= %d\n", getppid());
		} else {
		printf("segnale ricvuto dal padre sigusr2 con pid=%d\n", getppid());
			}
			return;
}
