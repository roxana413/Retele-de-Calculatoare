/* cliTcpConc.c - Exemplu de client TCP
   Trimite un nume la server; primeste de la server "Hello nume".
         
   Autor: Lenuta Alboaie  <adria@infoiasi.ro> (c)2009
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

/* codul de eroare returnat de anumite apeluri */
extern int errno;

/* portul de conectare la server*/
int port;

int main(int argc, char *argv[])
{
  int sd;                    // descriptorul de socket
  struct sockaddr_in server; // structura folosita pentru conectare
  char msg[100];             // mesajul trimis

  /* exista toate argumentele in linia de comanda? */
  if (argc != 3)
  {
    printf("Sintaxa: %s <adresa_server> <port>\n", argv[0]);
    return -1;
  }

  /* stabilim portul */
  port = atoi(argv[2]);

  /* cream socketul */
  if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("Eroare la socket().\n");
    return errno;
  }

  /* umplem structura folosita pentru realizarea conexiunii cu serverul */
  /* familia socket-ului */
  server.sin_family = AF_INET;
  /* adresa IP a serverului */
  server.sin_addr.s_addr = inet_addr(argv[1]);
  /* portul de conectare */
  server.sin_port = htons(port);

  /* ne conectam la server */
  if (connect(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
  {
    perror("[client]Eroare la connect().\n");
    return errno;
  }
  // printf("%sred\n", KRED);
  // printf("%sgreen\n", KGRN);
  // printf("%syellow\n", KYEL);
  // printf("%sblue\n", KBLU);
  // printf("%smagenta\n", KMAG);
  // printf("%scyan\n", KCYN);
  // printf("%swhite\n", KWHT);
  // printf("%snormal\n", KNRM);
  printf("%sUrmatoarele comenzi sunt disponibile: \n 1. login : <<username>>\n 2. logout\n 3. quit\n 4. afisare produse\n 5. afisare categorii\n 6. afisare <<categorie>>\n 7. selectare produs <<categorie>> <<produs>>\n 8. afisare cos\n 9. plasare comanda\n10. sterge <<produs>>\n", KGRN);
  while (1)
  {
    /* citirea mesajului */
    int lungimew = 0;
    int lungimer = 0;
    bzero(msg, 100);
    printf("%s[client]Introduceti o comanda: ", KMAG);
    fflush(stdout);
    read(0, msg, 100);

    lungimew = strlen(msg);
    /* trimiterea mesajului la server */
    if (write(sd, &lungimew, sizeof(int)) <= 0)
    {
      perror("[client]Eroare la write() spre server.\n");
    }
    if (write(sd, msg, sizeof(int) * lungimew) <= 0)
    {
      perror("[client]Eroare la write() spre server.\n");
      return errno;
    }

    /* citirea raspunsului dat de server 
     (apel blocant pina cind serverul raspunde) */
    char message[1000];
    bzero(message,1000);
    if (read(sd, &lungimer, sizeof(int)) <= 0)
    {
      perror("[client]Eroare la read() de la server.\n");
    }
    if (read(sd, message, sizeof(int) * lungimer) < 0)
    {
      perror("[client]Eroare la read() de la server.\n");
      return errno;
    }
    /* afisam mesajul primit */
    printf("[client]%sMesajul primit este: %s\n", KYEL, message);

    if (strstr(message, "Aplicatia a fost inchisa cu succes."))
    {
      close(sd);
      break;
    }
  }
  /* inchidem conexiunea, am terminat */
  close(sd);
}