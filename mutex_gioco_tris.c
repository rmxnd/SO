/*
 mutex_tris.c

il main thread deve:
° inizializzare il campo da gioco: una matrice di caratteri 3x3;
° creare 2 tread: giocatore_1 e giocatore_2;
° assegnare il turno ai giocatori;
° stampare il campo da gioco dopo la mossa di ogni giocatore;
° controlla ad ogni mossa se qualuno ha vinto;
° quando un giocatore vince: stampa un messaggio, cancella i thread, rimuove i mutex e termina;
*
ogni thread deve:
° richiedere all'utente la riga e la colonna da spuntare;
° assegna alla matrice il valore 'X' o 'O';
° attendere il turno successivo;
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


#define N 3
#define M 3


char campo[N][M];
int turno = 0;	// 0 main, 1 G1, 2 G2
pthread_mutex_t mutex;

void stampa_campo();
char controlla_vittoria();	// spazio: continua; X: vince G1; O: vince G2; P: parità
void *giocatore_1(void *arg);
void *giocatore_2(void *arg);


int main(int argc, char **argv)
{
	int r, c, giocatore = 1;	// righe, colonne
	char risultato;
	pthread_t g1, g2;

	// inizializzo il campo vuoto (matrice 3x3)
	for (r=0; r<N; r++){	// righe
		for(c=0; c<M; c++){	// colonne
			campo[r][c] = ' ';
		}
	}

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&g1, NULL, giocatore_1, NULL);
	pthread_create(&g2, NULL, giocatore_2, NULL);

	// finchè un giocatore vince
	while (1){
		while(1){
			// quando un giocatore finisce il turno, modifica il valore della variabile turno (condivisa)
			pthread_mutex_lock(&mutex);

			if (turno == 0){
				break;	// si esce dal while piu interno
			} else {
				pthread_mutex_unlock(&mutex);
				sleep(1);	// cancellation point, termina prima il thread 1 e poi il 2
			}
		}
		stampa_campo();
		risultato = controlla_vittoria();

			if(risultato == 'X'){
				printf("vince Giocatore 1\n");
				break;
			} else if (risultato == 'O'){
				printf("vince Giocatore 2\n");
				break;
			} else if (risultato == 'P'){
				printf("Parità\n");
				break;
			}
		if (giocatore == 1){
			turno = 1;	// perche tocca al giocatore_1
			giocatore = 2;	// così al ciclo successivo toccherà al giocatore_2
		} else {
			turno = 2;
			giocatore = 1;
		}
		pthread_mutex_unlock(&mutex);
	}	// fine primo while

	pthread_cancel(g1);
	pthread_cancel(g2);
	pthread_mutex_unlock(&mutex);
	 pthread_join(g1, NULL);
	 pthread_join(g2, NULL);
	pthread_mutex_destroy(&mutex);

	return 0;
}


void *giocatore_1(void *arg){
	int riga, colonna;

		while (1){
			while (1){
				pthread_mutex_lock(&mutex);
				if(turno == 1){
				break;
				}	else {
				pthread_mutex_unlock(&mutex);
				sleep(1);
				}
			}

	// ancòra con il mutex locked si chiede all'utente di inserire riga e colonna finchè non sono quelle corrette
			while (1){
				printf("Giocatore 1 è il tuo turno\n");
				printf("Riga: ");
				scanf("%d*c", &riga);

				printf("Colonna: ");
				scanf("%d*c", &colonna);

				if (campo[riga][colonna] == ' '){
					break;
				}
			}
			campo[riga][colonna] = 'X';

			turno = 0;
			pthread_mutex_unlock(&mutex);
		}	// fine primo while
	return NULL;
	}


void *giocatore_2(void *arg){
		int riga, colonna;

		while (1){
			while (1){
				pthread_mutex_lock(&mutex);
				if(turno == 2){
				break;
				}	else {
				pthread_mutex_unlock(&mutex);
				sleep(1);
				}
			}

	// ancòra con il mutex locked si chiede all'utente di inserire riga e colonna finchè non sono quelle corrette
			while (1){
				printf("Giocatore 2 è il tuo turno\n");
				printf("Riga: ");
				scanf("%d*c", &riga);

				printf("Colonna: ");
				scanf("%d*c", &colonna);

				if (campo[riga][colonna] == ' '){
					break;
				}
			}
			campo[riga][colonna] = 'O';

			turno = 0;
			pthread_mutex_unlock(&mutex);
		}	// fine primo while
	return NULL;
	}


void stampa_campo(){
			printf("\n\t\t\t %c | %c | %c\n" "\t\t\t___________\n", campo[0][0], campo[0][1], campo[0][2]);
			printf("\n\t\t\t %c | %c | %c\n" "\t\t\t___________\n", campo[1][0], campo[1][1], campo[1][2]);
			printf("\n\t\t\t %c | %c | %c\n", campo[2][0], campo[2][1], campo[2][2]);
		return;
		}


char controlla_vittoria() {
		int r, c; // riga, colonna

		for (c=0; c<M; c++){ // controllo colonne
			if (campo[0][c] == ' ') continue;
			if (campo[0][c] == campo[1][c] && campo[1][c] == campo[2][c]){
				return campo[0][c];
			}
		}

		for (r=0; r<N; r++) {// controllo righe
			if(campo[r][0] == ' ') continue;
			if (campo[r][0] == campo[r][1] && campo[r][1] == campo[r][2]) {
				return campo[r][0];
			}
		}

		// controllo diagonale
		if(campo[0][0] == campo[1][1] && campo[0][0] == campo[2][2] && campo[0][0] != ' '){
			return campo[0][0];
		}

		// controllo diagonale inversa
		if(campo[0][2] == campo[1][1] && campo[1][1] == campo[2][0] && campo[0][2] != ' '){
			return campo[1][1];
		}

		// controllo che il campo non sia pieno
		for (r=0; r<N; r++){
			for(c=0; c<M; c++){
				if(campo[r][c] == ' '){
					return ' ';
				}
			}
		}	// fine primo for

		// se arriva qui, parita'
		return 'P';
	}
