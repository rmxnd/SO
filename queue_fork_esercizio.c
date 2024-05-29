/*
queue_fork_esercizio.c

il padre crea un figlio.
i 2 processi comunicano con code di msg.
il figlio attende un msg contenente un int, lo moltiplica per 3, lo invia al padre, termina.
il padre attende 1 secondo, invia un msg al figlio con un int random tra 2 e 10, attende la risposta del figlio, stampa il valore ricevuto, rimuove la coda, termina.
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <time.h>


struct data {
	int val;
	};

struct msg_buffer {
	long msg_type;
	struct data d;
	};


int main(int argc, char **argv)
{
	pid_t pid;
	int msg_id, snd, rcv, rm, random_num;
	key_t key;
	struct msg_buffer message;


	if (key = ftok ("queue_fork_esercizio.c", 1234) == -1){
		perror ("errore ftok\n");
		exit(EXIT_FAILURE);
	}

	// creazione coda
	if ((msg_id = msgget (key, IPC_CREAT | 0666)) == -1){
		perror ("errore msgget\n");
		exit(EXIT_FAILURE);
		}

	pid = fork();

 swicth (pid){
		case 0:	// child
			if (rcv = msgrcv(msg_id, &message, sizeof(struct data), 2, 0) == -1){
		perror ("errore msgrcv\n");
		exit(EXIT_FAILURE);
		}

		printf("[figlio]: ricevuto msg '%d'\n", message.d.val);

		message.d.val *= 3;
		message.msg_type = 1;

		// invio al padre
		if (snd = msgsnd(msg_id, &message, sizeof(struct data), 0) == -1){
		perror ("errore msgsnd\n");
		exit(EXIT_FAILURE);
		}

		exit(EXIT_SUCCESS);

		case -1:
			perror("errore fork\n");
			exit(EXIT_FAILURE);

		default:
		break;
	}

	// parent
	sleep(1);
	random_num = rand() % (9+2);
	printf("[padre]: invio al figlio il numero: %d\n", random_num);

	// invia msg al figlio
	message.msg_type = 2;
	message.d.val = random_num;

	if (snd = msgsnd (msg_id, &message, sizeof(struct data), 0) == -1){
		perror ("errore msgsnd\n");
		exit(EXIT_FAILURE);
		}

	// attesa di risposta dal figlio
	if (rcv = msgrcv(msg_id, &message, sizeof(struct data), 1, 0) == -1){
		perror ("errore msgrcv\n");
		exit(EXIT_FAILURE);
		}

	printf("[padre]: ricevuto dal figlio il messaggio '%d'\n", message.d.val);

	// rimozione coda
	if (rm = msgctl(msg_id, IPC_RMID, NULL) == -1){
		perror ("errore msgctl, rimozione coda\n");
		exit(EXIT_FAILURE);
		}

	return 0;
}

