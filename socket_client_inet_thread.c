/*
socket_client_inet_thread.c
*
*
 */


#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#define PORT 9877


typedef struct {
	int a, b;
	} fattori;


int main(int argc, char **argv)
{
	int sock, fine, prodotto;
	fattori dato;
	struct sockaddr_in serv_addr;


	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

		// crea il socket
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("errore socket\n");
		exit(EXIT_FAILURE);
		}

			// stabilisce la connessione col server
		if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1){
		perror("errore socket\n");
		exit(EXIT_FAILURE);
		}

	while(1) {
		printf("inserire il primo int da inviare al server:\t");
		scanf("%d%*c", &dato.a);
		printf("inserire il secondo int da inviare al server:\t");
		scanf("%d%*c", &dato.b);

		printf("[client PID: %d] dati inviati al server: %d , %d\n", getpid(), dato.a, dato.b);
		write(sock, &dato, sizeof(fattori));
		read(sock, &prodotto, sizeof(int));
		printf("[client PID: %d] prodotto ricevuto dal server: %d\n", getpid(), prodotto);

		printf("0 per finire (zero)\n");
		scanf("%d%*c", &fine);
		if(!fine) break;

		}

	close(sock);	// chiude la connessione
	exit(EXIT_SUCCESS);
}

