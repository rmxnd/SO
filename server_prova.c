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


int main () {
    int sock_fd, new_sock_fd;
    struct sockaddr_in addr;
    char *buf="ciao dal server";
    struct in_addr inp;

    sock_fd = socket (AF_INET, SOCK_STREAM, 0);

    addr.sin_family=AF_INET;
    addr.sin_port=htons(PORT);
    addr.sin_addr.s_addr=inet_aton("127.0.0.1", &inp);
    bind (sock_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(sock_fd, 5);
   new_sock_fd = accept(sock_fd, (struct sockaddr *)&addr, (socklen_t *)sizeof(addr));

    write(sock_fd, (void *)buf, strlen(buf));
    printf("tutto ok");

    close (sock_fd);
    exit(EXIT_SUCCESS);
}