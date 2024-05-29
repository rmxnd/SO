#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>

#define FIGLI 3
#define LOOP_FIGLI 5
#define LOOP_PADRE 15

struct data{
	int indir_figlio;
	int val;
	pid_t pid;
	};

struct message{
	int mtype;
	struct data d;
	};

void f_figlio (int num, int msgid);


int main(int argc, char **argv)
{
	pid_t pid;
	int msg_id;
	struct message msg;


	msg_id = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);

	for(int i=0; i<FIGLI; i++) {
		switch(pid = fork()) {
			case -1:
				perror("errore fork\n");
				msgctl (msg_id, IPC_RMID, NULL);
				exit(EXIT_FAILURE);

			case 0:
				f_figlio(i+2, msg_id);	// i+2 (=0+2, 1+2, ...) perche deve assegnare '1' al padre
				exit(EXIT_SUCCESS);

			default:
				break;
		}
	}

	for(int i=0; i<LOOP_PADRE; i++){
		msgrcv(msg_id, (void *)&msg, sizeof(struct data), 1, 0);
		printf("[PADRE] msg ricevuto %d dal figlio %d\n", msg.d.val, msg.d.indir_figlio);

		msg.mtype=msg.d.indir_figlio;
		msg.d.val= 2* msg.d.val;
		msgsnd(msg_id, (void *)&msg, sizeof(struct data), 0);
		sleep(1);
		}

	msgctl (msg_id, IPC_RMID, NULL);
	exit(EXIT_SUCCESS);
}


void f_figlio (int num, int msgid){
	struct message msg;

		for(int j=0; j<LOOP_FIGLI; j++) {
			msg.mtype=1;
			msg.d.indir_figlio=num;
			msg.d.pid=getpid();
			msg.d.val=rand()%10+1;

			msgsnd(msgid, (void *)&msg, sizeof(struct data), 0);
			printf("[FIGLIO %d] inviato msg %d\n", msg.d.pid, msg.d.val);
			msgrcv(msgid, (void *)&msg, sizeof(struct data), num, 0);
			}
	}