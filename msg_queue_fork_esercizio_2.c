/*
msg_queue_fork_esercizio_2.c

# esercizio 4 tutorato 24/01/2024
* il processo padre (P0) genera 2 figli (P1, P2);
* la coda di msg cntiene un int (temoeratura) + un int (PID del processo che manda il msg);
* P0 per 10 volte, con sleep(1): riceve un msg (estrazione da coda FIFO), stampa il msg ricevuto (temp + PID), dopo 10 iterazioni rimuove la coda di msg;
* P1 e P2 per 5 volte, con sleep(1): inviano a P0 la temp (random tra 1 e 40), + PID, e terminano dopo 5 volte;
 */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>

#define N 2	// n° figli
#define F 5	// cicli figli
#define P 10 // cicli padre

struct data{
	int indirizzo, valore;
	pid_t pid;
	};

struct message{
	long mtype;
	struct data d;
	};

void funzione_figlio (int indirizzo, int msg_id);


int main(int argc, char **argv)
{
	pid_t pid;
	int i, msg_id, rcv, ctl;
	struct message msg;


	if((msg_id = msgget(IPC_PRIVATE, 0666 | IPC_CREAT)) == -1){
		perror("errore msgget\n");
		exit(EXIT_FAILURE);
	}

	for (i=0; i<N; i++){
		pid = fork();

		switch(pid){
			case -1:
				perror("errore fork\n");
				if((ctl = msgctl(msg_id, IPC_RMID, NULL)) == -1){
					perror("errore msgctl\n");
					exit(EXIT_FAILURE);
					}
				exit(EXIT_FAILURE);

			case 0:	// figlio
				funzione_figlio(i+2, msg_id);
				exit(EXIT_SUCCESS);

			default:
			break;
		}
	}
	// padre P0
	for (i=0; i<P; i++){
		if((rcv = msgrcv(msg_id, (void *)&(msg), sizeof(struct data), 1, 0)) == -1){
			perror("errore msgrcv\n");
			exit(EXIT_FAILURE);
			}
		printf("[Padre] temperatura ricevuta: %d da figlio: %d\n", msg.d.indirizzo, msg.d.pid);
		sleep(1);
		}

	msgctl(msg_id, IPC_RMID, NULL);
	exit(EXIT_SUCCESS);
}


void funzione_figlio (int indirizzo, int msg_id){
	struct message msg;
	int i, snd;

	for (i=0; i<F; i++){
		msg.mtype=1;
		msg.d.indirizzo=indirizzo;
		msg.d.pid=getpid();
		msg.d.valore=rand()%40+10;
		if ((snd = msgsnd(msg_id, (void *)&msg, sizeof(struct data), 0)) == -1){
			perror("errore msgsnd\n");
			exit(EXIT_FAILURE);
			}
		printf("[Figlio %d]messagio inviato: %d\n", msg.d.pid, msg.d.valore);
		sleep(1);
	}


	return;
	}