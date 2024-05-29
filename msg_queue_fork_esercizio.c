/*
msg_queue_fork_esercizio.c

* un padre crea 3 figli;
* il padre assegna ad ogni figlio un indirizzo intero >1 ed 1 a se stesso;
* ogni figlio per 5 volte: invia un msg con un int casuale tra 1 e 10 + il proprio PID e attende un int dal padre;
* il padre, dopo la creazione del figlio, per 15 volte: riceve 1 msg (estrazione dalla queue FIFO), invia al figlio un msg con l'int ricevuto x2, sleep(1), al termine del ciclo rimuove la coda e termina;
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>


#define N 3 // cicli fork
#define F 5 // figlio
#define P 15 // padre


struct data {
	int indirizzo_figlio;
	int valore;
	pid_t pid;
	};

struct message {
	long mtype;       /* message type, must be > 0 */
	struct data d;    /* message data */
	};


void funzione_figlio(int indirizzo, int msgid);


int main(int argc, char **argv)
{
	int i, msgid, ctl, rcv, snd;
	pid_t pid;
	struct message msg;

	if((msgid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT)) == -1) {
		perror("errore msgget\n");
		exit(EXIT_FAILURE);
	}

	for (i=0; i<N; i++){
		pid = fork();

		switch (pid){
			case -1:
				perror("errore fork\n");
				if ((ctl = msgctl(msgid, IPC_RMID, NULL)) == -1) {
					perror("errore msgget\n");
					exit(EXIT_FAILURE);
					}
				exit(EXIT_FAILURE);

			case 0:
			funzione_figlio(i+2, msgid);
			exit(EXIT_SUCCESS);

			default:
			break;
		}
	}

	for (i=0; i<P; i++){
		if((rcv = msgrcv(msgid, (void *)&msg, sizeof(struct data), 1, 0)) == -1){
			perror("errore msgrcv\n");
			exit(EXIT_FAILURE);
			}
		printf("[Padre] msg ricevuto %d dal figlio: %d \n", msg.d.valore, msg.d.indirizzo_figlio);
		msg.mtype = msg.d.indirizzo_figlio;
		msg.d.valore = msg.d.valore*2;
		if((snd = msgsnd(msgid, (void *)&msg, sizeof(struct data), 0)) == -1){
			perror("errore msgsnd\n");
			exit(EXIT_FAILURE);
			}
		printf("[Padre] msg inviato %d \n", msg.d.valore);
		sleep(1);
	}
	printf("eliminazione coda\n");
	if((ctl = msgctl(msgid, IPC_RMID, NULL)) == -1){
		perror("errore msgctl\n");
		exit(EXIT_FAILURE);
		}
	exit(EXIT_SUCCESS);
}


void funzione_figlio(int indirizzo, int msgid){
	struct message msg;
	int i, snd, rcv;

	for(i=0; i<F; i++){
		msg.mtype=1;
		msg.d.indirizzo_figlio=indirizzo;
		msg.d.pid=getpid();
		msg.d.valore=rand()%10+1;

		if((snd = msgsnd(msgid, (void *)&msg, sizeof(struct data), 0)) == -1){
			perror("errore msgsnd\n");
			exit(EXIT_FAILURE);
			}
		printf("[Figlio %d] messagio inviato %d \n", msg.d.pid, msg.d.valore);

		rcv = msgrcv(msgid, (void *)&msg, sizeof(struct data), indirizzo, 0);
		if (rcv == -1){
			perror("errore msgrcv\n");
			exit(EXIT_FAILURE);
			} else if (rcv > 0) {
				printf("[Figlio %d] messagio ricevuto dal padre %d \n", msg.d.pid, msg.d.valore);
			}
	}
	return;
	}