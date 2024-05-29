/*
socket_server_local_esempio.c

fa riferimento a socket_client_local_esempio.c
 */


#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>


#define PORT 8080
#define BUFFER_SIZE 32


int main(int argc, char **argv)
{
	int server_fd, new_socket;
	struct sockaddr_in address;
	int opt = 1;	// option
	int addrlen = sizeof (address);
	char buffer[BUFFER_SIZE] = {0};
	char *hello = "ciao dal server\n";


	// creazione unnamed socket
	unlink ("server_socket");	// rimozione precedenti socket
	server_fd = socket (AF_UNIX, SOCK_STREAM, 0);
		if (server_fd == -1) {
			perror ("errore socket\n");
			exit (EXIT_FAILURE);
		}

	// opzioni del socket
	if (setsockopt (server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1) {
		perror("errore setsockopt\n");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = PORT;

	// socket binding
	if (bind (server_fd, (struct sockaddr *)&address, addrlen) == -1 ) {
		perror ("errore bind\n");
		exit (EXIT_FAILURE);
	}

	// listening
	if (listen (server_fd, 3) < 0) { /* 3= maximum length of queue  of pending connections */
		perror ("errore listen\n");
		exit(EXIT_FAILURE);
	}

	// accepting
	if (new_socket = accept (server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen) == -1) {
		perror ("errore accept\n");
		exit(EXIT_FAILURE);
	}

	// ricezione dati dal client
	if (read (new_socket, buffer, BUFFER_SIZE) == -1) {
		perror ("errore read\n");
		exit(EXIT_FAILURE);
	}
	printf ("[client msg]: %s\n", buffer);

	// invio di un msg al clinet
	if (send (new_socket, hello, strlen(hello), 0) == -1){
		perror ("errore send\n");
		exit(EXIT_FAILURE);
		}

	return 0;
}

