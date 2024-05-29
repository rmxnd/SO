/*
msg_queue_2.c

usando i meccanismi ipc system V, creare un processo figlio.
il padre deve mandare al figlio una stringa tramite coda di msg e il figlio stampa la stringa ricevuta
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>


struct msgbuf {
	char str[] = "stringaaaa";
	};

struct mymsg {
	long mtype = 1;
	struct msgbuf message;
	} msg;	// msg.message.str

int main(int argc, char **argv)
{
	pid_t pid = 0;
	int queue = 0;


	pid = fork();
	switch (pid){
	case 0:	// child
	queue = msgrcv (msgid, (void *)msg.message.str, strlen(msg.message.str), 1, 0);
		if (queue == -1){
			perror("errore msgrcv\n");
			exit(EXIT_FAILURE);
		}
	break;

	case -1:
	printf("errore fork\n");
	exit(EXIT_FAILURE);
	break;

	default:	// parent
		int msgid = msgget (IPC_PRIVATE, IPC_CREAT | 0666);
			if (msgid == -1){
				perror("errore msgget\n");
				exit(EXIT_FAILURE);
			}
		printf("coda creata\n");
		queue = msgsnd (msgid, (void *)msg.message.str, strlen(msg.message.str), 0);
			if (queue == -1){
				perror("errore msgsnd\n");
				exit(EXIT_FAILURE);
			}
		printf("messaggio mandato in coda...\n");
		}	// fine switch

	return 0;
}

