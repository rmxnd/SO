/*
socket_client_local.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>


int main(int argc, char **argv)
{
	int sockfd, len, result;
	struct sockaddr_un address;
	char ch = 'A';

	// create clien socket
	sockfd = socket (AF_UNIX, SOCK_STREAM, 0);

	// name the socket, agreed to the server
	address.sun_family = AF_UNIX;
	strcpy(address.sun_path, "server_socket");
	len = sizeof (address);

	// connect to the server socket
	result = connect (sockfd, (struct sockaddr *)&address, len);
	if (result == -1) {
		perror ("errore client\nconnect\n");
		exit(EXIT_FAILURE);
	}

	// read/writhe
	write (sockfd, &ch, 1);
	read (sockfd, &ch, 1);
	close (sockfd);

	return 0;
}

