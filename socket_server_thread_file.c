/*
socket_server_thread_file.c
*
server concorrente per la memorizzazione di file;
accetta la connessione TCP, crea un thread (worker_thread) detached per gestire la connessione;
il thread riceve una stringa la client (show/ upload/ download);
se upload: riceve file e lo salva come <nome_file>, chiude la connessione, termina;
se download: invia il file, chiude la connessione, termina;
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>


#define SERVER_PORT 38888
#define FILE_NAME_LEN 200

void *worker_thread (void *args);
void file_upload (int sock, const char *filename);
void file_download (int sock, const char *filename);


int main(int argc, char **argv)
{
	struct sockaddr_in addr;
	int ssock, wsock;
	pthread_t wt;
	pthread_attr_t attr;


	// inizializzazione attributi thread
	pthread_attr_init(&attr);
	if (pthread_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0){
		perror("errore creazione thread_detached\n");
		exit(EXIT_FAILURE);
	}

	// creazione socket e inizializzazione server
	addr. sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if ( (ssock = socket (AF_INET, SOCK_STREAM, 0) == -1){
		perror("errore socket\n");
		exit(EXIT_FAILURE);
	}

	if (bind (ssock, (struct sockaddr *)&addr, (socklen_t)sizeof(addr)) == -1){
	perror("errore bind\n");
	close(ssock);
	exit(EXIT_FAILURE);
	}

	if (listen(ssock, 5) == -1){
	perror("errore listen\n");
	exit(EXIT_FAILURE);
	}

	if (pthread_create(&wt, &attr, worker_thread, (void *)wsock) != 0) {
		perror("errore creazione thread\n");
		close(wsock);
		} else {
		printf ("nuova connessione accettata\n");
		}

	// chiusura socket e uscita
	close(ssock);
	printf("bye\n");
	exit(EXIT_SUCCESS);
	return 0;
}


void *worker_thread (void *args) {
	int len,  sock = (int)args;
	char buffer[FILE_NAME_LEN + 9];

	len = read (sock, (void *)buffer, FILE_NAME_LEN);
		if (len == 0) {
			printf("connessione chiusa dal client\n");
		} else if (len > 0) {
			if ( strncmp (buffer, "upload", 6) == 0) {
				file_upload (sock, &(buffer[7]));
			} else if (strncmp (buffer, "download", 8 == 0)) {
				file_download (sock, &(buffer[9]));
			} else {
			printf ("comando (%s) non supportato", buffer);
			}
		}
	close(sock);
	return;
	}


void file_upload (int sock, const char *filename) {
	int fd;
	char path[FILE_NAME_LEN+13];
	char buffer[BUFSIZ];
	size_t len;
	unsigned int totlen = 0;

	sprintf(path, "server files/%s", filename);
	printf("uploading file: %s\n", filename);

	if ((fd = open (path, O_CREAT, | O_WRONLY, 0666)) == -1){
		perror ("errore open (upload)\n");
		return;
	}

	do {
		len = read (sock, buffer, BUFSIZ);
		if (len > 0) {
			write (fd, buffer, len);
			totlen += len;
		}
	}
	while (len > 0)
		close (fd);
		printf ("upload completato. bytes: %u \n", totlen);

	return;
	}


void file_download (int sock, const char *filename) {
	int fd;
	char path[FILE_NAME_LEN+13];
	char buffer[BUFSIZ];
	size_t len;
	unsigned int totlen = 0;

	sprintf(path, "server files/%s", filename);
	printf("Downloading file: %s\n", filename);

	if ((fd = open (path, O_RDONLY)) == -1){
		perror ("errore open (download)\n");
		return;
	}

	do {
		len = read (fd, buffer, BUFSIZ);
		if (len > 0) {
			write (sock, buffer, len);
			totlen += len;
		}
	}
	while (len > 0){
		close (fd);
		printf ("download completato. bytes: %u \n", totlen);
	}
	return;
	}