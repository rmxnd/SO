/*
 * thread_somma_matrice.c
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define RIGHE 10
#define COLONNE 10
int matrix[RIGHE][COLONNE];
void *thread_somma (void *);

int main(int argc, char **argv)
{
	int i, j, num=1, totale=0;
	int risultato[RIGHE];	// vettore in cui ogni thread salva il risultato
	pthread_t tid[RIGHE];
	
	//	riempimento matrice
	for(i=0; i<RIGHE; i++){
	for (j=0; j<COLONNE; j++){
		matrix[i][j] = num;
		num++;
		}	
	}
	
	//	creazione n° thread = n° RIGHE
	for (i=0; i<RIGHE; i++){
		pthread_create(&(tid[i]), NULL, thread_somma, (void *)i);		
	}
	
	//	attesa di fare la join su un thread già terminato
	for (i=0; i<RIGHE; i++){
		pthread_join(tid[i], NULL);		
	}
	
	for (i=0; i<RIGHE; i++){
		totale += risultato[i];
		}
	printf("totale = %d\n", totale);
	return 0;
}


void *thread_somma (void *arg){
	int i, r = (int)arg;
	int risultato[r];
	
	for (i=0; i<COLONNE; i++){
		risultato[r] += matrix[r][i];	
		}
		return NULL;
	}
