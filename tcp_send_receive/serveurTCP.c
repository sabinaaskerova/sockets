#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "check.h"

#define BL 5 //backlog pour listen
//./serveurTCP 5000
int main(int argc, char **argv){
    if(argc != 2)
    {
      printf("Usage: %s port_local\n", argv[0]);
      exit(-1);
    }

    int sockfd;
    CHECK((sockfd = socket(AF_INET, SOCK_STREAM, 0)) != -1); //pas besoin de mettre IPPROTO_TCP on peut mettre 0

    struct sockaddr_in my_addr;
    struct sockaddr_in client;
    socklen_t fromlen = sizeof(struct sockaddr_in); 

    my_addr.sin_addr.s_addr =  htonl(INADDR_ANY);
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(atoi(argv[1]));

    CHECK(bind(sockfd, (struct sockaddr*) &my_addr, fromlen)!=-1);
    CHECK(listen(sockfd, BL)!=-1);
    int sock_recv = accept(sockfd, (struct sockaddr*) &client, &fromlen); //accept remplit l'adresse du client automatiquement

    char buf[1024]; 
    memset(buf, '\0', 1024);

    CHECK(recv(sock_recv, buf, 1024, 0)!=-1);
    printf("%s\n", buf);
    char str_client[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(client.sin_addr), str_client, INET_ADDRSTRLEN);
    printf("%s\n", str_client);
    printf("%d\n", client.sin_port);


    CHECK(close(sockfd)!=-1);

    return 0;

}