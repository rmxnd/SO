#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>


#define N 5
typedef struct {
    unsigned int vettore[N];
    float media;
    } info;
float media (info *p, int dim);


int main () {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;

    
    if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("errore socket\n");
        exit(EXIT_FAILURE);
         }
    printf("socket creato\n");

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){
        perror("errore bind\n");
        exit(EXIT_FAILURE);
         }
    printf("bind eseguita\n");
    
    if (listen(server_sock, 5) == -1){
        perror("errore listen\n");
        exit(EXIT_FAILURE);
         }
    printf("server in ascolto\n");

    if (accept(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){
        perror("errore accept\n");
        exit(EXIT_FAILURE);
         }
    printf("connessione accettata\n");


    exit(EXIT_SUCCESS);
}


float media (info *p, int dim){
    int res;

    for (int i=0; i<dim; i++){
        res += p->vettore[i];
    }
    return (res/dim);
}