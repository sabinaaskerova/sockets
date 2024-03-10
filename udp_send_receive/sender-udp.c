#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
// ./sender-udp 0.0.0.0 3700 "Salut"

int main(int argc, char **argv)
{
  int sockfd;                      // descripteur de socket
  struct sockaddr_in dest;         // structure d'adresse qui contiendra les
                                   // parametres reseaux du destinataire

  // verification du nombre d'arguments sur la ligne de commande
  if(argc != 4)
    {
      printf("Usage : %s @dest num_port chaine_a_envoyer\n", argv[0]);
      exit(-1);
    }
  

  // creation de la socket
  sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
  if(sockfd==-1){
    perror("erreur socket ");
    exit(EXIT_FAILURE); 
  }

  // initialisation de la structure d'adresse du destinataire :

  // famille d'adresse
  dest.sin_family = AF_INET;

  // adresse IPv4 du destinataire

  inet_aton(argv[1], &(dest.sin_addr));
  /*
  if(inet_pton(AF_INET, "0.0.0.0", &dest.sin_addr) != 1){
    perror("inet_pton");
    close(sockfd);
    exit(EXIT_FAILURE);
  }
  
*/
  // port du destinataire
  int my_port = atoi(argv[2]);
  dest.sin_port = htons(my_port); //htons(port);


  // envoi de la chaine
  
  int size = strlen(argv[3]);
  if(sendto(sockfd, argv[3], size, 0, (struct sockaddr*) &dest, sizeof(dest)) == -1)
    {
      perror("erreur a l'appel de la fonction sendto -> ");
      close(sockfd);
      exit(EXIT_FAILURE);
    }
    

  // fermeture de la socket
  close(sockfd);

  return 0;
}
