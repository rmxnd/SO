/*
 sem_stampa.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>


#define MAX_DOCS 10
sem_t sem;


void stampa_doc (int id);


int main(int argc, char **argv)
{
	int docs[MAX_DOCS];
	sem_init(&sem, 0, 1);	// inizializza sem

	for (int i=0; i<MAX_DOCS; i++){
		docs[i] = i;	// crea l'array
	}

	for (int i=0; i<MAX_DOCS; i++){
		sem_wait(&sem);	// acquisisce sem
		stampa_doc(docs[i]);	// stampa
		sem_post(&sem);	// rilascia sem
	}

	return 0;
}


void stampa_doc (int id){
	printf("stampando il doumento %d\n", id);
	// posso mettere una sleep(1)
	return;
	}
