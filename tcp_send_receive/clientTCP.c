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
//./clientTCP  0.0.0.0 5000 "h"
int main(int argc, char **argv){
  if(argc != 4)
    {
      printf("Usage : %s @dest num_port chaine_a_envoyer\n", argv[0]);
      exit(-1);
    }

    int sockfd;
    CHECK((sockfd = socket(AF_INET, SOCK_STREAM, 0)) != -1);

    
    struct sockaddr_in serveur;
    socklen_t fromlen = sizeof(struct sockaddr_in); 

    serveur.sin_addr.s_addr =  htonl(INADDR_ANY);
    serveur.sin_family = AF_INET;
    serveur.sin_port = htons(atoi(argv[2]));

    CHECK(connect(sockfd, (struct sockaddr*) &serveur, fromlen)!=-1);

    int size = strlen(argv[3]);
    CHECK(send(sockfd, argv[3], size, 0));

    CHECK(close(sockfd)!=-1);

    return 0;
    
}