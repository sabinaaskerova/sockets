#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//./receiver-udp 3500
int main(int argc, char **argv)
{
  int sockfd;                   // descripteur de socket
  char buf[1024];               // espace necessaire pour stocker le message recu

  // taille d'une structure sockaddr_in utile pour la fonction recvfrom
  socklen_t fromlen = sizeof(struct sockaddr_in); 

  struct sockaddr_in my_addr;   // structure d'adresse qui contiendra les param reseaux du recepteur
  struct sockaddr_in client;    // structure d'adresse qui contiendra les param reseaux de l'expediteur

  // verification du nombre d'arguments sur la ligne de commande
  if(argc != 2)
    {
      printf("Usage: %s port_local\n", argv[0]);
      exit(-1);
    }

  // creation de la socket
  sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
  if(sockfd==-1){
    perror("erreur socket ");
    exit(EXIT_FAILURE); //-------
  }
  // initialisation de la structure d'adresse du recepteur (pg local)

  my_addr.sin_addr.s_addr =  htonl(INADDR_ANY);
  // famille d'adresse
  my_addr.sin_family = AF_INET;
  memset(buf, '\0', 1024);

  // recuperation du port du recepteur
  my_addr.sin_port = htons(atoi(argv[1]));

  // adresse IPv4 du recepteur
  //inet_aton(, &(my_addr.sin_addr)); //pas vraiment besoin


  // association de la socket et des param reseaux du recepteur
  if(bind(sockfd, (struct sockaddr*) &my_addr, fromlen) != 0) //pq sizeof sockaddr_in et pas sockaddr
    {
      perror("erreur lors de l'appel a bind -> ");
      exit(-2);
    }
  

  // reception de la chaine de caracteres
  if(recvfrom(sockfd, buf, 1024, 0, (struct sockaddr*) &client, &fromlen) == -1) //client pour pouvoir repondre au message
    {
      perror("erreur de reception -> ");
      exit(-3);
    }

  // affichage de la chaine de caracteres recue
  printf("%s\n", buf);
  //sleep(20);

  // fermeture de la socket
  if(close(sockfd)==-1){
    perror("erreur close");
  };

  return 0;
}
