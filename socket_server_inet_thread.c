/*
socket_server_inet_thread.c

* il server, ciclicamente accetta una connesione sulla porta 9877 e crea un worker thread detached che gestiste la connessione col client;
* il worker thread: ° attende dal client la ricezione di una struct contenente 2 int;
 °calcola il prodotto dei 2 int;
 ° invia il risultato al client;
 ° continua dal primo punto finche non rileva la disconnessione del client, altrimenti chiude la connessione col client e termina;
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>



#define PORT 9877

typedef struct {
	int a, b;
	} fattori;

void *product (void *args);


int main(int argc, char **argv)
{
	int sock, addrlen;
	int *client_sock;
	char addr[20];
	pthread_t worker_thread;
	pthread_attr_t thread_attr;
	struct sockaddr_in serv_addr, client_addr;


		if (pthread_attr_init(&thread_attr) != 0){
			perror("errore pthread_attr_init\n");
			exit(EXIT_FAILURE);
			}

		if (pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED) != 0){
			perror("errore pthread_attr_setdetachstate\n");
			exit(EXIT_FAILURE);
			}

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("errore socket\n");
		exit(EXIT_FAILURE);
		}

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(PORT);
		addrlen = (socklen_t)sizeof(serv_addr);

	if (bind(sock, (struct sockaddr *)&serv_addr, addrlen) == -1){
		perror("errore bind\n");
		exit(EXIT_FAILURE);
		}

	if (listen(sock, 5) == -1){	// creazione coda di connessioni e messa in ascolto
		perror("errore bind\n");
		exit(EXIT_FAILURE);
		}

	while (1){
		client_sock = (int *)malloc(sizeof(int));
		if ((*client_sock = (sock, (struct sockaddr *)&client_addr, (socklen_t *)&addrlen)) == (int *)-1){
		perror("errore accept\n");
		exit(EXIT_FAILURE);
		}
		printf("[Server] connessione col client creata\n");

		if (inet_ntop(AF_INET, &client_addr.sin_addr, addr, (socklen_t)sizeof(addr)) != NULL){
			perror("errore inet_ntop\n");
			exit(EXIT_FAILURE);
			}
		printf("IP client: %s\nPorta client: %d", addr, ntohs(client_addr.sin_port));


		if (pthread_create(&worker_thread, &thread_attr, product, (void *)client_sock) != 0){
			perror("errore pthread_create\n");
			exit(EXIT_FAILURE);
			}
		}

	return 0;
}


void *product (void *args){
	int prodotto, descriptor = *(int *)args;
	fattori dato;

	while(read(descriptor, &dato, sizeof(fattori)) > 0){
		prodotto = dato.a*dato.b;
		write(descriptor, &prodotto, sizeof(int));
	}
	close(descriptor);
	free(args);
	pthread_exit(NULL);
	return NULL;
	}