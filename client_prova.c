#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h> 

#define PORT 9876
#define SIZE 30


int main () {
    int client_sock;
    struct sockaddr_in addr;
    char buf[SIZE];

    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    connect(client_sock, (struct sockaddr *)&addr, sizeof(addr));
    read(client_sock, buf, strlen(buf));

    printf("dal server: %s\nletti %d byte\n", buf, (int)strlen(buf));
    close(client_sock);
    exit(EXIT_SUCCESS);
}