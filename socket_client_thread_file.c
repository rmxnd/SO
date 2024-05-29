/*
socket_client_thread_file.c
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


void file_upload (int sock, const char *filename);
void file_download (int sock, const char *filename);


int main(int argc, char **argv)
{
	struct sockaddr_in addr;
	int sock;
	char cmd[FILE_NAME_LEN+9];

	// creazione socket e inizializzazionbe server
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	inet_aton ("127.0.0.1", &(addr.sin_addr));

	sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock == -1){
			perror("socket eerror\n");
			exit(EXIT_FAILURE);
		}

	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1){
		perror ("connect error\n");
		close(sock);
		exit(EXIT_FAILURE);
	}

	printf("inserisci comando\n");
	fgets(cmd, FILE_NAME_LEN+9, stdin);
	cmd[strlen(cmd)-1]='\0';

	if ( (strncmp(cmd, "upload", 6)) == 0) {
		write(sock, cmd, strlen(cmd)+1);
		file_upload(sock, &(cmd[7]));
	} else if ((strncmp(cmd, "download", 8)) == 0) {
		write(sock, cmd, strlen(cmd)+1);
		file_download(sock, &(cmd[9]));
	} else {
		printf("comando non supportato (%s)\n", cmd);
	}

		close(sock);
		printf("Bye\n");
		exit(EXIT_SUCCESS);
	return 0;
}


void file_upload (int sock, const char *filename) {
	int fd;
	char path[FILE_NAME_LEN+13], buffer[BUFSIZ];
	size_t len;
	unsigned int totlen = 0;

	sprintf(path, "client files/%s", filename);
	printf("uploading file: %s\n", filename);

	if ((fd = open (path, O_RDONLY)) == -1){
		perror ("errore open (upload)\n");
		return;
	}

	do {
		len = read (fd, buffer, BUFSIZ);
		if (len > 0) {
			totlen += write (sock, buffer, len);
		}
	}
	while (len > 0)

	close(fd);
	printf("upload completato.\nBytes: %u \n", totlen);
	return;
	}


void file_download (int sock, const char *filename) {
	int fd;
	char path[FILE_NAME_LEN+13], buffer[BUFSIZ];
	size_t len;
	unsigned int totlen = 0;

	sprintf(path, "client files/%s", filename);
	printf("downloading file: %s\n", filename);

	if ((fd = open (path, O_CREAT | O_WRONLY, 0666)) == -1){
		perror ("errore open (download)\n");
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

	close(fd);
	printf("download completato.\nBytes: %u \n", totlen);
	return;
	}