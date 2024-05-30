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
    int client_s;
    struct sockaddr_in client_addr;
    socklen_t len;
    char client_buf[SIZE];

    client_s = socket (AF_INET, SOCK_STREAM, 0);
    len = sizeof(client_addr);
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    client_addr.sin_port = htons(PORT); 
    connect(client_s, (struct sockaddr *)&client_addr, len);

    // comunicazione con server
    while(1) {
        printf("inserire un msg: ""end"" per terminare\t");
        fgets(client_buf, SIZE, stdin);
        write(client_s, client_buf, SIZE);
        read(client_s, client_buf, SIZE);
        printf("msg dal server: %s\n", client_buf);
        if (strncmp (client_buf, "end", 3) == 0) break;
    }

    close(client_s);
    exit(EXIT_SUCCESS);
    }