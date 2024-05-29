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


int main(int argc, char **argv)
{
	int sock;
	struct sockaddr_in serv_addr;
	char tx_buf[LEN], rx_buf[LEN];


	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if ((sock = socket (AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("errore socket\n");
		exit(EXIT_FAILURE);
		}
	printf("socket creato\n");

	connect (sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	printf("connessione accettata\n");

		read (sock, rx_buf, LEN);
	printf("[CLIENT] ricevuto: %s\n", rx_buf);

	if(fgets (tx_buf, LEN, stdin) == NULL) {
		perror("errore fgets\n");
		close(sock);
		exit(EXIT_FAILURE);
		}

	tx_buf[strlen(tx_buf)-1] = '\0';
	if (write (sock, tx_buf, strlen(tx_buf)+1) == -1) {
		perror("errore write\n");
		close(sock);
		exit(EXIT_FAILURE);
		}

	if (read (sock, rx_buf, LEN) == -1) {
		perror("errore read\n");
		close(sock);
		exit(EXIT_FAILURE);
		}
	printf("[CLIENT] ricevuto: %s\n", rx_buf);
	close(sock);
	exit(EXIT_SUCCESS);
}