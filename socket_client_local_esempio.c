/*
socket_client_local_esempio.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


#define PORT 8080
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 32


int main(int argc, char **argv)
{
	int valread, sock = 0;
	struct sockaddr_in serv_addr;
	char *hello = "ciao dal client";
	char buffer[BUFFER_SIZE] = {0};

	// creazione socket
	if ( (sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror ("errore creazione socket\n");
		exit(EXIT_FAILURE);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	if (inet_pton(AF_INET, SERVER_IP, (void *)&serv_addr.sin_addr) <= 0){
		perror ("errore inet_pton, indirizzo non valido\n");
		exit(EXIT_FAILURE);
	}

	// connessione al server
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
		perror ("errore connect\n");
		exit(EXIT_FAILURE);
	}

	// invio msg al server
	if (send (sock, hello, strlen(hello), 0) == -1) {
		perror ("errore send\n");
		exit(EXIT_FAILURE);
	}
	printf("[client] messaggio inviato al server\n");

	// ricezione risposta dal server
	if ( (valread = read(sock, buffer, BUFFER_SIZE)) == -1) {
		perror("errore lettura risposta del server al client\n");
		exit(EXIT_FAILURE);
	}
	printf("[client] messaggio dal server: %s\n", buffer);
	return 0;
}