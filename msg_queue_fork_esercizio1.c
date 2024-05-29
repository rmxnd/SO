#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <string.h>

struct data {
	int num;
	char string[10];
	};

 struct msgbuf {
               long mtype;       /* message type, must be > 0 */
               struct data d;;    /* message data */
           };


int main(int argc, char **argv)
{
	pid_t pid;
	int msgid;
	struct msgbuf buf;
	char *da_copiare = "siaoo";

	msgid = msgget (IPC_PRIVATE, 0666 | IPC_CREAT);
	buf.mtype=1;
	strcpy(buf.d.string, da_copiare);
	msgsnd(msgid, &buf, sizeof(struct data), 0);
	printf("[PADRE] msg inviato %s\n", buf.d.string);
	pid = fork();

	if (pid <0) exit(EXIT_FAILURE);
	else if (pid == 0) {
		msgrcv(msgid, &buf, sizeof(struct data), 1, 0);
		printf("[FIGLIO] ricevuto %s\n", buf.d.string);
	}


	exit(EXIT_SUCCESS);
}

