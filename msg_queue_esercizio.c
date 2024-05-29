/*
msg_queue_esercizio.c

° il processo padre genera N figli
° il processo padre assegna ad ogni figlio un indirizzo (intero > 1) e a se st6esso 1;
° ciclicamente, per X volte, il processo padre interroga ogni figlio richiedendo un valore indicante il n° di richieste e il figlio lo stampa a video;
° dopo X richiest, il padre invia un segnale di terminazione ai figli e ne attende la terminazione
° utilizzo una coda di messaggi per la comunicazione tra padre e figli
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>


#define X 5
#define N 10
#define RICHIESTA 0
#define RISPOSTA 1
#define TERMINAZIONE 2


struct message {
	long int mtype;	// per indirizzare un msg ad un processo specifico ( 1=Padre)
	int command;	// 0=Richiesta, 1=Risposta, 2=Uscita;	(personalizzati)
	int value;
	};


void figlio (int addr, int msgid);


int main(int argc, char **argv)
{
	int msgid, i, snd, rcv, ctl;
	pid_t pid;
	key_t key;
	struct message msg;

	// creazione key
	key = ftok ("msg_queue_esercizio.c", 0444);
		if ( key == -1 ) {
			perror ( "errore ftok\n" );
			exit ( EXIT_FAILURE );
		}

		// creazione coda
	msgid = msgget (IPC_PRIVATE, 0666 | IPC_CREAT);
		if ( msgid == -1 ) {
			perror ( "errore msgget\n" );
			exit ( EXIT_FAILURE );
		}

	for (i=0; i<N; i++){
		pid = fork();

		switch (pid){
			case -1:
				printf("errore fork\n");
				exit(EXIT_FAILURE);
			break;

			case 0:
				figlio((i+2), msgid);
				exit(EXIT_SUCCESS);
			break;

			default:
			break;
		}	// fine switch
	}	// fine for

	for (i=0; i<X; i++) {
		for (int j=0; j<N; j++){
			msg.mtype = j+2;
			msg.command = TERMINAZIONE;
			snd = msgsnd (msgid, (void *)&msg, sizeof (struct message) - sizeof (long int), 0);
				if ( snd == -1 ) {
				perror ( "errore msgsnd\n" );
				exit ( EXIT_FAILURE );
				}

			rcv = msgrcv (msgid, (void *)&msg, sizeof (struct message) - sizeof (long int), 1, 0);
				if ( rcv == -1 ) {
					perror ( "errore msgrcv\n" );
					exit ( EXIT_FAILURE );
					}
			printf ("ricevuto messaggio: %d\n", msg.value);
			}	// fine for interno
	}	// fine primo for

	for (int j=0; j<N; j++){
		msg.mtype = j+2;
		msg.command = TERMINAZIONE;
		snd = msgsnd (msgid, (void *)&msg, sizeof ( struct message) - sizeof (long int), 0);
			if (wait(NULL) == -1){
				perror ("errore wait\n");
				exit (EXIT_FAILURE);
				}
	}
	ctl = msgctl (msgid, IPC_RMID, NULL);
		if ( ctl == -1 ) {
			perror ( "errore msgctl\n" );
			exit ( EXIT_FAILURE );
				}
	return 0;
}


void figlio (int addr, int msgid){
	struct message msg, response;
	int rcv, snd;

	response.mtype = 1;	// per il padre
	response.command = RISPOSTA;
	response.value = 0;

	while (1) {
		rcv = msgrcv ( msgid, (void *)&msg, sizeof ( struct message ) - sizeof ( long int ), addr, 0);
			if ( rcv == -1 ) {
				perror ( "errore msgrcv\n" );
				exit ( EXIT_FAILURE );
			}
			switch (msg.command) {
				case TERMINAZIONE:
					exit (EXIT_SUCCESS);
				break;

				case RICHIESTA:
					response.value++;
					snd = msgsnd (msgid, (void *)&response, sizeof (struct message ) - sizeof (long int ), 0);
					if ( snd == -1 ) {
						perror ( "errore msgsnd\n" );
						exit ( EXIT_FAILURE );
						}
				break;

				default:
					perror ( "errore switch\n");
					exit ( EXIT_FAILURE );
				break;
			}	// fine switch

	}

	return;
	}
