/*
msg_queue_esempio.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MSGSZ 32

struct mymsg {
	char str[MSGSZ];
	};

 struct msgbuf {
               long mtype;       /* message type, must be > 0 */
               struct mymsg msg;    /* message data */
           };



int main(int argc, char **argv)
{
	key_t key;
	int msqid, snd, buf_len;
	struct msgbuf sbuf;	// variabile "sbuf", di tipo "struct msgbuf"

	// creazione chiave
	if (key = ftok ( "msg_queue_esempio.c", 1234 ) == -1 ) {
	perror ("errore ftok");
	exit (EXIT_FAILURE);
	}

	// creazione coda
	if ( msqid = msgget ( key, 0644 | IPC_CREAT ) == -1 ) {
	perror ("errore msgget\n");
	exit(EXIT_FAILURE);
	}

	// invio messaggio
	sbuf.mtype = 1;	//	priority
	strcpy (sbuf.msg.str, "questo e' un msg di esempio\n");
	buf_len = strlen (sbuf.msg.str) + 1;	// lunghezza msg

	if ( snd = msgsnd ( msqid, &sbuf, buf_len, 0 ) == -1 ) {
	perror ("errore msgsnd\n");
	exit (EXIT_FAILURE);
	}

	printf ("messaggio inviato: %s \n", sbuf.msg.str);
	return 0;
}

