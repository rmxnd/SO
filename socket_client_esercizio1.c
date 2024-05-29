#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

#define PORT 9876
#define DIM 30


int main(int argc, char **argv)
{
	int client_sock;
	struct sockaddr_in addr;
	socklen_t len;
	char rx_buf[DIM], buf[DIM];

	client_sock = socket (AF_INET, SOCK_STREAM, 0);

	len = sizeof(addr);
	addr.sin_family=AF_INET;
	addr.sin_port=htons(PORT);
	addr.sin_addr.s_addr=INADDR_LOOPBACK;
	connect (client_sock, (struct sockaddr *)&addr, len);
	printf("[client] connesso al server\n");

	read(client_sock, rx_buf, strlen(rx_buf));
	printf("[client] ricevuto: %s\n", rx_buf);

	if(strncmp(rx_buf, "CAMPIONA", 8) == 0){
		if ((time(NULL)%2)==0) strcpy(buf, "SOTTO_SOGLIA\0");
		else strcpy(buf, "SOGLIA_SUPERATA\0");
		write(client_sock, buf, strlen(buf)+1);
	}

	close(client_sock);
	exit(EXIT_SUCCESS);
}