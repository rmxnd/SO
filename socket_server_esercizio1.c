#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 9876
#define DIM 30


int main(int argc, char **argv)
{
	int server_socket, new_socket;
	struct sockaddr_in addr, client_addr;
	socklen_t len;
	char buf[DIM], rx_buf[DIM];


	server_socket = socket (AF_INET, SOCK_STREAM, 0);

	len = sizeof(addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = INADDR_LOOPBACK;
	bind(server_socket, (struct sockaddr *)&addr, len);

	listen (server_socket, 5);

	while(1) {
		new_socket = accept(server_socket, (struct sockaddr *)&client_addr, &len);

		strcpy(buf, "CAMPIONA\0");
		write(new_socket, &buf, strlen(buf)+1);

		read (new_socket, rx_buf, strlen(rx_buf));

		printf("[server] ricevuto: %s\n", rx_buf);
	}

	close(server_socket);
	close(new_socket);
	exit(EXIT_SUCCESS);
}

