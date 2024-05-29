/*
 sem_fork_file_esercizio.c

 * creare un padre e un figlio che condividon un file di testo (il cui nome deve essere inserito da tastiera);
 * il figlio: appena creato, scrive sul file una frase inserita da tastiera;
 * quando il figlio conclude la scrittura, il padre legge la frase scritta dal figlio, la visualizza e termina;)
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


#define N 32


int main(int argc, char **argv)
{
	pid_t pid;
	char nome_file[N], frase_da_inserire[N], frase_da_leggere[N];
	int fd;


		printf("inserire nome file:\t");
		scanf("%s*c", nome_file);

		if ((fd = open(nome_file, O_CREAT | O_TRUNC | O_RDWR, 0666)) == -1){
			perror("errore open\n");
			exit(EXIT_FAILURE);
		}
		printf("file creato: %s\n", nome_file);

	pid=fork();
	switch (pid){
		case -1:
			perror("errore fork\n");
			exit(EXIT_FAILURE);

		case 0:	// figlio
			printf("inserire frasee da scrivere su file:\t");
			fgets(frase_da_inserire, N, stdin);
			if (write(fd, frase_da_inserire, N) == -1){
			perror("errore write\n");
			exit(EXIT_FAILURE);
				}
			exit(EXIT_SUCCESS);

		default:
			break;
	}
		// padre
		wait(NULL);
		if (lseek(fd, 0, SEEK_SET) == (off_t)-1){
			perror("errore lseek\n");
			exit(EXIT_FAILURE);
				}
		if (read(fd, frase_da_leggere, N) == -1){
			perror("errore read\n");
			exit(EXIT_FAILURE);
				}
		if (close(fd) == -1){
			perror("errore close\n");
			exit(EXIT_FAILURE);
				}
			printf("nel file c'è scritto: %s\nfine programma\n", frase_da_leggere);
	exit(EXIT_SUCCESS);
}

