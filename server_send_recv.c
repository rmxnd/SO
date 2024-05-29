#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define PORT 7777
#define SIZE 30

struct msg {
	pid_t pid;
	int rand;
	};


int main(int argc, char **argv)
{
	int server_socket, rcvd_num;
	struct sockaddr_in addr, client_addr;
	socklen_t client_len, len = sizeof(addr);
	struct msg buf[SIZE];
	ssize_t bytesrcvd;
	char *response;


	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = INADDR_ANY;
	bind(server_socket, (struct sockaddr *)&addr, len);
	listen(server_socket, 5);
	printf("in ascolto...");

	while (1) {
		client_len = sizeof(client_addr);
		bytesrcvd = recvfrom (server_socket, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, client_len);

		rcvd_num = buf->rand;
		printf("ricevuto: %d\n", rcvd_num);

		if (rcvd_num >= 12) response = "hai vinto";
			else response = "hai perso";
		sendto (server_socket, response, strlen(response), 0, (struct sockaddr *)&client_addr, client_len);

	}

	close(server_socket);
	return 0;
}

