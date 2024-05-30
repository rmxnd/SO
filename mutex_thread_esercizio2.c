/*
mutex_thread_esercizio2.c

* main thread + secondario: condividono 1 variabile =1;
*  main thread: crea thread secondario e per 5 volte: stampa il valore della variabile condivisa, attende che il thread secondario processi la variabile, dopo 5 cicli assegna -1 alla variabile condivisa, attende la terminazione del thread secondario e termina esso stesso;
* thread secondario: finche' la variabile e' != -1 : somma un valore random tra 1 e 10 alla variabile, altrimenti termina;
* utilizzare mutex e una seconda variabie condivisa per definire che il secondo thread ha processato la variabile;
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main(int argc, char **argv)
{

	return 0;
}

