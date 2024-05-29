/*
msg_queue_receive.c

 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/msg.h>


#define BUFSIZE 128

struct my_msg_str {
long int my_msg_type;
char some_text[BUFSIZE];
	};


int main(int argc, char **argv)
{
	int msgid, running = 1;
	struct my_msg_str some_data;
	long int msg_to_receive = 0;

	msgid = msgget ((key_t)1234, 0666 | IPC_CREAT);
		if (msgid == -1){
			fprintf(stderr, "msgget failed, errno: %d\n", errno);
			exit (EXIT_FAILURE);
		}

	while (running){
		if (msgrcv (msgid, (void *)&some_data, BUFSIZE, msg_to_receive, 0) == -1) {
			fprintf(stderr, "msgrcv failed with errno: %d\n", errno);
			exit(EXIT_FAILURE);
		}
	printf ("hai scritto: %s\n", some_data.some_text);

	if (strncmp (some_data.some_text, "end", 3) == 0 ) {
		running = 0;
		}
	}

	if (msgctl (msgid, IPC_RMID, 0) == -1) {
		fprintf(stderr, "msgctl failed with errno: %d \n", errno);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
	return 0;
}

