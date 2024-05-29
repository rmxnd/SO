/*
 * socket_server_thread_mutex.c

 messaggistica remota
 * server: attende la connessione da piu client e, stabilita la connessione, il server avvia il Worker_thread che gestisce la comunica<ione tra server/client, server attende un comando fino a quando non viene chiusa la connessione ( stringa) e invia una risposta; ---> SBLA (socket, bind, listen, accept);
 * client: dopo aver stabilito la connesione, crea un thread secondario che invia un comando di lettura per chiedere al server l'ultimo msg inviato, attende risposta dal server e lo stampa, il thread principale richiede all'utente di inserire un comando da tastiera;
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <arpa/inet.h>


#define N 128


void *worker_thread (void *args);
void f (int sig);


struct dati {
	char messagio[N], utente[N];
	int id;
	};


struct dati ultimo_msg;
pthread_mutex_t mutex;
int ssock;


int main(int argc, char **argv)
{
	int csock;
	struct sockaddr_in saddr;
	pthread_t tid;
	pthread_attr_t tattr;

	signal(SIGINT, f);
	signal(SIGTSTP, f);

	// inizializzo la struct dati condivisa
	ultimo_msg.id=0;
	ultimo_msg.messagio[0]='\0';
	ultimo_msg.utente[0]='\0';

	pthread_mutex_init(&mutex, NULL);	// inizializzo mutex

	// inizializzo attributi thread
	pthread_attr_init(&tattr);
	pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_DETACHED);

	// creazione socket stream dominio internet
	if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("errore socket\n");
		exit(EXIT_FAILURE);
	}

	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(9876);
	saddr.sin_addr.s_addr=htonl(INADDR_ANY);
	if (bind(ssock, (struct sockaddr *)&saddr, sizeof(saddr)) == -1){
		perror("errore bind\n");
		exit(EXIT_FAILURE);
	}

	// server in ascolto
	listen(ssock, 5);

	while(1){
		// accetta connessione
		csock=accept(ssock, (struct sockaddr *)&saddr, (socklen_t *)sizeof(saddr));
		pthread_create(&tid, &tattr, worker_thread, (void *)csock);
	}
	exit(EXIT_SUCCESS);
}


void *worker_thread (void *args){
	int len, sock=(int)args;
	char buff[N], utente[N];

	while(1){
		len = read(ssock, buff, N);

		if(strncmp("read", buff, 4)==0){
			pthread_mutex_lock(&mutex);
			snprintf(buff, sizeof(buff), "%d %s: %s", ultimo_msg.id, ultimo_msg.utente, ultimo_msg.messagio);
			pthread_mutex_unlock(&mutex);
			write (ssock, buff, strlen(buff)+1);	// invio risposta
		} else if ((strncmp("close", buff, 5)) == 0){
			close(ssock);
			break;
		} else if ((strncmp("send", buff, 4))==0){
			pthread_mutex_lock(&mutex);
			ultimo_msg.id++;
			strcpy(ultimo_msg.utente, utente);
			strncpy(ultimo_msg.messagio, &buff[5], len-5);
			pthread_mutex_unlock(&mutex);
			sprintf(buff, "ok");
			write(sock, buff, 8);
		} else if((strncmp("register", buff, 8)) == 0){
			strncpy(utente, &buff[9], len-9);
			sprintf(buff, "Welcome %s!", utente);
			write(sock, buff, strlen(buff)+1);	// invio risposta
		}
	}	// fine while
	return NULL;
	}


void f (int sig){
	printf("Arrivedorci\n");
	close(ssock);
	exit(EXIT_SUCCESS);
	}