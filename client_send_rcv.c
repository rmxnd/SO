#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define PORT 7777
#define SIZE 30
#define LOOP 5

struct msg {
	pid_t pid;
	int rand;
	};


int main(int argc, char **argv)
{
	int client_sock;
	struct sockaddr_in addr;
	socklen_t len;
	char buf[SIZE];
	struct msg message;
	ssize_t rcvd_bytes;

	client_sock = socket(AF_INET, SOCK_DGRAM, 0);

	addr.sin_family=AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	len = sizeof(addr);
	bind(client_sock, (struct sockaddr *)&addr, len);

	for(int i=0; i<LOOP; i++){
		message.pid = getpid();
		message.rand =	rand()%25+1;
		sendto(client_sock, &message, sizeof(struct msg), 0, (struct sockaddr *)&addr, len);

		rcvd_bytes= recvfrom(client_sock, buf, sizeof(buf), 0, NULL, NULL);
		buf[rcvd_bytes]='\0';
		printf("risposta dal server: %s\n", buf);
		sleep(1);
	}

	close(client_sock);
	return 0;
}

