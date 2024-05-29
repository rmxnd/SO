/*
socket_client_thread_mutex.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>



#define PORT 9876
#define N 100
void *thread_func (void *args);


int main(int argc, char **argv)
{
	struct sockaddr_in addr;
	int sock;
	char username[N], buff[N], msg[N];
	pthread_t tid;

	sock = socket(AF_INET, SOCK_STREAM, 0);

	addr.sin_family=AF_INET;
	addr.sin_port =htons(PORT);
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	printf("inserire username:\t");
	fgets(username, N, stdin);
	username[strlen(username)-1]='\0';

	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) <0){
		perror("errore connect\n");
		exit(EXIT_FAILURE);
	}
	pthread_create(&tid, NULL, thread_func, (void *)&sock);
	snprintf(buff, N, "register %s", username);
	write(sock, buff, strlen(buff)+1);
	while(1){
		printf("inserire msg\n");
		fgets(msg, N-10, stdin);
		msg[strlen(msg)-1]='\0';

		if(strncmp(msg, "close", 5)==0){
			strcpy(buff, "close");
			write(sock, buff, strlen(buff)+1);
			break;
	} else {
		snprintf(buff, N, "send %s\n", msg);
		write(sock, buff, strlen(buff)+1);
		}
		sleep(1);
	}
	close(sock);
	printf("bye\n");
	exit(EXIT_SUCCESS);
}


void *thread_func (void *args){
	int sock=(int)args, r=1, mid=0, rid=0;
	char buff[N];

	while(1){
		sleep(1);
		strcpy(buff, "read");
		write(sock, buff, strlen(buff)+1);
		r=1;

		if(read(sock, buff, N) >0){
			if(strncmp(buff, "Welcome", 7) !=0 && strncmp(buff, "ok", 2) !=0) {
				sscanf(buff, "%d %*s\n", &mid);	// salvataggio id msg nella variabile
				r=0;
				if(mid != rid){
					printf("%s\n", buff);	// se l'id e' != dal precedente, lo stampa
					rid=mid;
				}
			} else {
				printf("%s\n", buff);
			}
		} else {
			pthread_exit(EXIT_SUCCESS);
		}
	}
	return NULL;
	}