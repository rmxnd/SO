/*
server_thread_detached.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9347
#define N 10
#define SIZE 5

typedef struct {
	int vettore[N];
	float media;
	} info;

float media( info *p, int dim);
void *connection_handler (void *arg);


int main(int argc, char **argv)
{
	pthread_t thread;
	pthread_attr_t attr;
	int server_sock, new_sock, client_len;
	struct sockaddr_in server_addr, client_addr;


	if((server_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("errore socket\n");
		exit(EXIT_FAILURE);
		}
	printf("socket creato");

	if (pthread_attr_init(&attr) != 0){
		perror("errore pthread_attr_init\n");
		exit(EXIT_FAILURE);
		}

	if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0){
		perror("errore pthread_attr_setdetachstate\n");
		exit(EXIT_FAILURE);
		}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr(INADDR_ANY);
	if(bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){
		perror("errore bind\n");
		close(server_sock);
		exit(EXIT_FAILURE);
		}
	printf("bind eseguita");
	listen (server_sock, 5);
	printf("in attesa di connessioni...");

	while (1) {
		client_len = sizeof(client_addr);
		if((new_sock = accept(server_sock, NULL, NULL)) == -1){
			perror("errore accept, connessione non accetata\n");
			exit(EXIT_FAILURE);
			}
		printf("connessione accettata");

	if(pthread_create (&thread, &attr, connection_handler, (void *)&new_sock) != 0){
		perror("errore pthread_create\n");
		exit(EXIT_FAILURE);
		}
	printf("thread detached creato\n");
	}

	close(server_sock);
	exit(EXIT_SUCCESS);
}


void *connection_handler (void *arg) {
	int res, ripeti = 1, socket = *(int *)arg;
	info message;

	while (ripeti) {
		res = read (socket, &message, sizeof(info));
		if (res == 0) ripeti = 0;
		else {
			message.media = media(&message, N);
			write (socket, &message, sizeof(info));
		}
	}

	printf("client disconnesso con successo\n");
	close(socket);
	pthread_exit(NULL);
	}


float media( info *p, int dim){
	float m=0;

	for (int i=0; i<dim; i++) m+=p->vettore[i];

	return (m/dim);
	}