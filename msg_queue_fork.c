/*
msg_queue_fork.c

usando i meccanismi ipc system V, creare un processo figlio.
il padre deve creare e mandare al figlio una stringa tramite coda di msg e il figlio stampa la stringa ricevuta
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/ipc.h>
#include <unistd.h>


#define MSGSZ 32

struct mymsg {
	char string[MSGSZ];
	};

struct msgbuf {
	long mtype;       /* message type, must be > 0 */
	struct mymsg msg;    /* message data */
	};


int main(int argc, char **argv)
{
	key_t key;
	int msqid, snd, buf_len, rcv;
	pid_t pid;
	struct msgbuf sbuf, rbuf;

	// priorita' e lunghezza del msg
	sbuf.mtype = 1;
	buf_len = sizeof (struct mymsg);

	// generazione key
	key = ftok ("msg_queue_fork.c", MSGSZ);
		if ( key == -1 ) {
			perror ( "errore ftok\n" );
			exit ( EXIT_FAILURE );
		}

	// creazione coda
	msqid = msgget ( key, 0644 | IPC_CREAT);
		if ( msqid == -1 ) {
			perror ( "errore msgget\n" );
			exit ( EXIT_FAILURE );
		}

	pid = fork();
	if ( pid == -1 ) {
		perror ( "errore fork\n" );
		exit ( EXIT_FAILURE );
	} else if (pid == 0 ) {	// figlio

	rcv = msgrcv (msqid, &rbuf, buf_len, 0, 0);
		if ( rcv == -1 ) {
			perror ( "errore msgrcv\n" );
			exit ( EXIT_FAILURE );
		}
		printf ("[Figlio]: messaggio ricevuto = %s \n" "sto uscendo...\n", rbuf.msg.string);	// uso la struct Rbuf	(riceve)
	} else {	// padre

	// invio del msg
	strcpy (sbuf.msg.string, "Messaggio_da_padre a figlio\n");
	snd = msgsnd (msqid, &sbuf, buf_len, 0);
		if ( snd == -1 ) {
			perror ( "errore msgsnd\n" );
			exit ( EXIT_FAILURE );
		}
		printf("[Padre]: messaggio inviato = %s \n", sbuf.msg.string);
	}	// fine padre
	return 0;
}