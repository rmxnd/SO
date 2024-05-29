/*
 file_prova.c
creazione e apertura di un file scrivendo strlen(buf) Bytes e poi leggendo N Bytes dal 3° Byte in poi
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>


#define N 5


int main(int argc, char **argv)
{
	int fd=0;
	const char *buf = "hello";
	char tmp[strlen(buf)-3];	// dove memorizzare i dati da prelevare dalla read

	fd = open("file_prova.txt", O_RDWR | O_RDWR, S_IWOTH | S_IROTH);
	write (fd, (void *)buf, strlen(buf));
	lseek (fd, +3, SEEK_SET);
	read (fd, (void *)tmp, N);

	printf("nel file c'e' scritto: %s\n", tmp);
	close(fd);
	printf("file chiuso correttamente\n");
	return 0;
}

