/*
msg_queue.c

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

#define X 5
struct message {
	long int message_type;	// per indirizzare un msg ad un processo specifico ( 1=Padre)
	int command;	// 0=Richiesta, 1=Risposta, 2=Uscita;	(personalizzati)
	int value;
	};
void figlio (int msgid, int addr);


int main(int argc, char **argv)
{
	int msgid, i;
	// key_t key = ftok ("msg_queue.c", 0444);
	msgid = msgget (IPC_PRIVATE, 0666 | IPC_CREAT);
	pid_t pid;

	for (i=0; i<N; i++){
		pid = fork();

		switch (pid){
			case -1:
			printf("errore fork\n");
			exit(EXIT_FAILURE);

			case 0:
			figlio(msgid, (i+2));
			exit(EXIT_SUCCESS);

			default:
			break;
		}

	}



	return 0;
}


void figlio (int msgid, int addr){

	return;
	}
