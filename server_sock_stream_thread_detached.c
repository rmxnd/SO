/*
server_sock_stream_thread_detached.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define PORT 8080
#define LEN 48
void *client_handler (void *arg);


int main(int argc, char **argv)
{
	int server_sock, client_sock;
	struct sockaddr_in server_addr, client_addr;
	char stringa[20];
	pthread_t thread;
	pthread_attr_t attr;


	if (pthread_attr_init (&attr) != 0) {
		perror("errore pthread_attr_init\n");
		exit(EXIT_FAILURE);
		}

	if (pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED) != 0) {
		perror("errore setdetachstate\n");
		exit(EXIT_FAILURE);
		}
	printf("thread detached creato\n");

	if ((server_sock = socket (AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("errore socket\n");
		exit(EXIT_FAILURE);
		}
	printf("socket creato\n");

	bind (server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
	printf("bind ok\n");

	if (listen (server_sock, 5) == -1){
		perror("errore listen\n");
		exit(EXIT_FAILURE);
		}
	printf("bind ok\n");

	while(1){
		if (accept (server_sock, NULL, NULL) == -1) {
			perror("errore accept\n");
			exit(EXIT_FAILURE);
			}
		printf("connessione accettata\n");

		if (pthread_create (&thread, &attr, client_handler, (void *)&client_sock) != 0) {
			perror("errore pthread_create\n");
			close (client_sock);
			exit(EXIT_FAILURE);
			}
		printf ("thread creato\n");
		}

	close (server_sock);
	exit(EXIT_SUCCESS);
}


void *client_handler (void *arg){
	int sock = *(int *)arg;
	char txbuf[LEN], rxbuf[LEN];

	// invio msg al client
	strcpy (txbuf, "di quale colore hai i capelli?");
	if (write (sock, txbuf, strlen(txbuf)+1) == -1) {
		perror("errore write\n");
		exit(EXIT_FAILURE);
		}
	printf ("scrittura completata\n");

	if (read (sock, rxbuf, LEN) == -1) {
		perror("errore read\n");
		close(sock);
		exit(EXIT_FAILURE);
		}

	printf("il colore dei capelli è: %s\n", rxbuf);
	strcpy(txbuf, "Fine\0");
	if (write (sock, txbuf, strlen(txbuf)+1) == -1) {
		perror("errore write\n");
		exit(EXIT_FAILURE);
		}

	close(sock);
	// pthread(exit);
	}