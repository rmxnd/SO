#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h> 
#include <string.h>

#define PORT 9876
#define SIZE 30


int main () {
    int server_sock, client_sock;
    socklen_t server_len, client_len;
    struct sockaddr_in server_addr, client_addr;
    char buf[SIZE];

    server_sock = socket (AF_INET, SOCK_STREAM, 0);
    
    server_len = strlen(server_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bind (server_sock, (struct sockaddr *)&server_addr, len);

    listen (server_sock, 5);
    client_len = sizeof(client_addr);
    client_sock = accept (server_sock, (struct sockaddr *)&client_addr, &client_len);

    // ricezione msg
    while (1) {
        read (client_sock, buf, SIZE);
        printf("msg ricevuto dal client = %s\ninserisci un msg", buf);
        fgets (buf, SIZE, stdin);
        write(client_sock, buf, SIZE);
        if(strncmp(buf, "end", 3) == 0) break;
    }

    close(server_sock);
    close(client_sock);
    exit(EXIT_SUCCESS);
    }