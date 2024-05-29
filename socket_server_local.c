/*
socket_server_local.c
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv)
{
	int server_sockfd, client_sockfd, server_len, client_len;
	struct sockaddr_un server_address, client_address;

	// rimozione precedenti socket
	unlink("server_socket");
	server_sockfd = socket (AF_UNIX, SOCK_STREAM, 0);

	// name the socket
	server_address.sun_family = AF_UNIX;
	strcpy (server_address.sun_path, "server_socket");
	server_len = sizeof(server_address);
	bind (server_sockfd, (struct sockaddr *)&server_address, server_len);

	// create connection queue
	listen(server_sockfd, 5);
	while (1) {
		char ch;
		printf("server waiting\n");
		client_len = sizeof (client_address);

		// accept a connection
		client_sockfd = accept (server_sockfd, (struct sockaddr *)&client_address, (socklen_t *)client_len);

		// read/write to client
		read(client_sockfd, &ch, 1);
		ch++;
		write(client_sockfd, &ch, 1);
		close (client_sockfd);
	}
	return 0;
}