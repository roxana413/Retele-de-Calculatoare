/* servTcpConc.c - Exemplu de server TCP concurent
    Asteapta un nume de la clienti; intoarce clientului sirul
    "Hello nume".
    */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

/* portul folosit */
#define PORT 2024
#define lungime_max 300

/* codul de eroare returnat de anumite apeluri */
extern int errno;
char *getName(char given_username[lungime_max])
{
    char username1[10] = {};
    char *result = malloc(lungime_max);
    int i, j;
    for (i = 0, j = 0; i < strlen(given_username); i++, j++)
        if (given_username[i] > 96 && given_username[i] < 123)
        {
            username1[j] = given_username[i];
        }
        else
        {
            j--;
        }
    username1[j] = 0;

    printf("%s", username1);
    strcpy(result, username1);
    return result;
}
int searchInFile(char *fname, char *str)
{
    FILE *fp;
    int line_num = 1;
    int find_result = 0;
    char temp[512];

    //gcc users
    if ((fp = fopen(fname, "r")) == NULL)
    {
        return (-1);
    }

    while (fgets(temp, 512, fp) != NULL)
    {
        if ((strstr(temp, str)) != NULL)
        {
            printf("A match found on line: %d\n", line_num);
            printf("\n%s\n", temp);
            find_result++;
        }
        line_num++;
    }
    //Close the file if still open.
    if (fp)
    {
        fclose(fp);
    }

    return find_result;
}

char *selectareProdusF(char categorie[], char nume[])
{
    char str[80] = {};
    const char s[2] = " ";
    char *token;
    char categorie_n[20] = {};
    int length;
    char fname[20] = {};
    char fname_user[20] = {};
    char extension[] = ".txt";
    char produs1[30] = {};
    int found = 0;
    char *result = malloc(lungime_max);
    FILE *folder;

    strcpy(str, categorie);
    /* get the first token */
    token = strtok(str, s);
    length = strlen(token);
    printf("Numele utilizatorului este:%s", nume);
    printf("Categoria este:%s.\n", token);
    printf("Produsul este:%s.\n", categorie + length + 1);
    strcpy(produs1, categorie + length + 1);
    printf("Produsul cautat este:%s.\n", produs1);
    //cream numele pentru cele 2 fisiere
    memcpy(categorie_n, categorie, length + 1);
    strcpy(fname, categorie_n);
    strcat(fname, extension);

    strcpy(fname_user, nume);
    strcat(fname_user, extension);
    printf("[server]Numele fisierului utlizatorului este:%s.\n", fname_user);

    printf("[server]Numele fisierului cautat este:%s\n", fname);
    found = searchInFile(fname + 1, produs1 + 1);
    printf("%d", found);
    if (found == 0)
        strcpy(result, "Ne pare rau dar produsul nu exista..");

    if (found == -1)
        strcpy(result, "Ne pare rau dar categoria nu exista...");

    if (found == 1)
    {
        //aduagam in cos
        if ((folder = fopen(fname_user, "a")) < 0)
            perror("Eroare la append in fisier");

        if (folder == NULL)
            perror("Eroare, fisier inexistent..");
        /* Append data to file */
        fputs(produs1 + 1, folder);
        fputs("\n", folder);
        fclose(folder);
        strcpy(result, "Produsul a fost adaugat cu succes in cosul de cumparaturi..");
    }
    return result;
}

char *loginf(char given_username[lungime_max])
{
    FILE *folder;
    int found = 0;
    char username[lungime_max] = {};
    char *result = malloc(lungime_max);
    int ok = 1;
    char username1[10] = {};

    int i, j;
    for (i = 0, j = 0; i < strlen(given_username); i++, j++)
        if (given_username[i] > 96 && given_username[i] < 123)
        {
            username1[j] = given_username[i];
        }
        else
        {
            j--;
        }
    username1[j] = 0;

    //printf("%s", username1);

    if ((folder = fopen("useri.ini", "r")) < 0)
        perror("Eroare la citirea din fisier");

    if (folder == NULL)
        perror("Eroare, fisier inexistent..");

    fflush(stdout);
    while (fgets(username, lungime_max, folder) != NULL)
    {
        printf("%s", "Sunt aici");
        char username2[lungime_max] = {};

        int i, j;
        for (i = 0, j = 0; i < strlen(username); i++, j++)
            if (username[i] != '\n')
            {
                username2[j] = username[i];
            }
            else
            {
                j--;
            }

        username2[j] = 0;

        //printf("%s", username);  //username e toata linia
        //printf("%s", username2); //username2 e taiat pana la prima aparitie a lui '\0'

        if (strcmp(username1, username2) == 0)

        {
            //printf("%s", "Sunt in if");
            found = 1;
            break;
        }
    }
    if (found == 1)
        strcpy(result, "Logarea a avut loc cu succes.");
    else
    {
        strcpy(result, "Username-ul dvs. nu apare in baza noastra de date.\n");
    }
    //printf("%s", result);
    return result;
    free(result);
}
char *afisare(char categorie[])
{
    printf("[server]Am intrat in functia de afisare..\n");
    printf("[server]Categoria aleasa:%s\n", categorie);

    char *buffer;
    FILE *folder;
    char folder_name[15] = {};
    char extension[] = ".txt";
    long lSize;

    strcpy(folder_name, categorie);
    strcat(folder_name, extension);
    printf("[server]Numele fisierului cautat este: %s\n", folder_name);

    if ((folder = fopen(folder_name, "r")) < 0)
        perror("Eroare la citirea din fisier");

    if (folder == NULL)
    {
        perror("Eroare, fisier inexistent..");
        return "Ne pare rau, dar categoria introdusa este inexistenta..";
        exit(EXIT_FAILURE);
    }

    fseek(folder, 0L, SEEK_END);
    lSize = ftell(folder);
    rewind(folder);

    /* allocate memory for entire content */
    buffer = calloc(1, lSize + 1);
    if (!buffer)
        fclose(folder), fputs("memory alloc fails", stderr), exit(1);

    /* copy the file into the buffer */
    if (1 != fread(buffer, lSize, 1, folder))
        fclose(folder), free(buffer), fputs("entire read fails", stderr), exit(1);

    /* buffer is a string contains the whole text */

    return buffer;

    fclose(folder);
    free(buffer);
}
char *afisareProduseF()
{
    char *buffer;
    FILE *folder;
    long lSize;

    if ((folder = fopen("produse.txt", "r")) < 0)
        perror("Eroare la citirea din fisier");

    if (folder == NULL)
        perror("Eroare, fisier inexistent..");

    fseek(folder, 0L, SEEK_END);
    lSize = ftell(folder);
    rewind(folder);

    /* allocate memory for entire content */
    buffer = calloc(1, lSize + 1);
    if (!buffer)
        fclose(folder), fputs("memory alloc fails", stderr), exit(1);

    /* copy the file into the buffer */
    if (1 != fread(buffer, lSize, 1, folder))
        fclose(folder), free(buffer), fputs("entire read fails", stderr), exit(1);

    /* buffer is a string contains the whole text */

    return buffer;

    fclose(folder);
    free(buffer);
}

char *plasareComandaF(char nume[])
{
    char *result;
    //verificam daca exista cosul de cumparaturi
    char folder_name[15] = {};
    char extension[] = ".txt";
    char cos[] = "cos";
    long lSize;
    char *buffer;
    FILE *fptr1, *fptr2;
    char c;
    char cos_folder_name[20] = {};

    printf("[server]Am intrat in functia de plasare comanda.\n");
    printf("[server]Numele utilizatorului este:%s\n", nume);

    strcpy(folder_name, nume);
    strcat(folder_name, extension);
    printf("[server]Numele fisierului cautat este: %s\n", folder_name);

    //cream un alt fisier de tipul numecos.txt
    strcpy(cos_folder_name, nume);
    strcat(cos_folder_name, cos);
    strcat(cos_folder_name, extension);
    printf("[server]Numele noului fisier care se va crea este:%s.\n", cos_folder_name);

    if ((fptr1 = fopen(folder_name, "r")) < 0)
        perror("Eroare la citirea din fisier");
    if (NULL != fptr1)
    {
        fseek(fptr1, 0, SEEK_END);
        int size = ftell(fptr1);

        if (0 == size)
        {
            printf("file is empty\n");
            return "Ne pare rau, dar cosul dumneavoastra de cumparaturi este gol..";
            exit(EXIT_FAILURE);
        }
    }

    if (fptr1 == NULL)
    {
        return "Ne pare rau, dar comanda dumneavoastra nu contine niciun articol..";
        perror("Eroare, fisier inexistent..");
        exit(EXIT_FAILURE);
    }

    //cream un alt fisier de tipul numecos.txt
    //copiem continutul primului fisier in al 2-lea
    //stergem primul fisier
    // Open another file for writing
    fptr2 = fopen(cos_folder_name, "w");
    if (fptr2 == NULL)
    {
        printf("Cannot open file %s \n", cos_folder_name);
        exit(0);
    }
    // Read contents from file
    c = fgetc(fptr1);
    while (c != EOF)
    {
        fputc(c, fptr2);
        c = fgetc(fptr1);
    }

    printf("\nContents copied to %s", cos_folder_name);
    fclose(fptr1);
    fclose(fptr2);
    if ((fptr1 = fopen(folder_name, "w")) < 0)
    {
        perror("Cannot delete the file %s \n");
        exit(EXIT_FAILURE);
    }
    fclose(fptr1);
    //remove(folder_name);
    return "Comanda dumnevoastra a fost plasata cu succes!";
}
char *afisareCosF(char nume[])
{
    char folder_name[15] = {};
    char extension[] = ".txt";
    long lSize;
    char *buffer;
    FILE *folder;
    char *response;

    printf("[server]Am intrat in functia de afisare cos..\n");
    printf("[server]Numele utilizatorului este:%s\n", nume);

    strcpy(folder_name, nume);
    strcat(folder_name, extension);
    printf("[server]Numele fisierului cautat este: %s\n", folder_name);

    if ((folder = fopen(folder_name, "r")) < 0)
    {
        perror("Eroare la citirea din fisier");
        return "Ne pare rau, dar cosul dumneavoastra de cumparaturi este gol..";
        exit(EXIT_FAILURE);
    }
    if (folder == NULL)
    {
        perror("Eroare, fisier inexistent..");
        return "Ne pare rau, dar cosul dumneavoastra de cumparaturi este gol..";
        exit(EXIT_FAILURE);
    }
    // if (NULL != folder)
    // {
    //     fseek(folder, 0, SEEK_END);
    //     int size = ftell(folder);

    //     if (0 == size)
    //     {
    //         printf("file is empty\n");
    //         return "Ne pare rau, dar cosul dumneavoastra de cumparaturi este gol..";
    //         exit(EXIT_FAILURE);
    //     }
    // }
    char c = fgetc(folder);
    if (feof(folder))
    {
        printf("Data file is emtpy, exiting the program");
        return "Ne pare rau, dar cosul dumneavoastra de cumparaturi este gol..";
        exit(EXIT_FAILURE);
        exit(0);
    }

    fseek(folder, 0L, SEEK_END);
    lSize = ftell(folder);
    rewind(folder);

    /* allocate memory for entire content */
    buffer = calloc(1, lSize + 1);
    if (!buffer)
        fclose(folder), fputs("memory alloc fails", stderr), exit(1);

    /* copy the file into the buffer */
    if (1 != fread(buffer, lSize, 1, folder))
        fclose(folder), free(buffer), fputs("entire read fails", stderr), exit(1);

    /* buffer is a string contains the whole text */

    return buffer;

    fclose(folder);
    free(buffer);
}
char *stergereProdusF(char produs[], char nume[])
{
    char *result = malloc(sizeof(char) * lungime_max);
    FILE *folder;
    char folder_name[20] = {};
    char extension[] = ".txt";

    strcpy(folder_name, nume);
    strcat(folder_name, extension);
    printf("Numele fisierul cautat este:%s.\n", folder_name);
    printf("Numele produsului cautat este:%s.\n", produs);
    if ((folder = fopen(folder_name, "r")) < 0)
        perror("Eroare la citirea din fisier");

    //verificam daca clientul are un cos de cumparaturi
    if (folder == NULL)
    {
        perror("Eroare, fisier inexistent..");
        strcpy(result, "Ne pare rau, dar cosul dumneavoastra este gol..");
    }
    //parcurgem fisierul

    //verificam daca produsul este in cos
    int found = searchLine(folder_name, produs);
    if (found > 0)
    {
        deleteF(folder_name, produs);
        //eliminam produsul din cos
        strcpy(result, "Produsul a fost eliminat cu succes din cosul de cumparaturi.");
    }
    else
    {
        strcpy(result, "Produsul selectat nu este in cos.");
    }

    return result;
}

void deleteF(char filename[], char word[])
{
    FILE *fileptr1, *fileptr2;
    char ch;
    int delete_line, temp = 1;

    //open file in read mode
    fileptr1 = fopen(filename, "r");
    ch = getc(fileptr1);
    char words[20][20];
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = getc(fileptr1);
    }
    //rewind
    rewind(fileptr1);

    delete_line = searchLine(filename, word);

    //open new file in write mode
    fileptr2 = fopen("replica.c", "w");
    ch = 'A';
    while (ch != EOF)
    {
        ch = getc(fileptr1);
        //except the line to be deleted
        if (temp != delete_line)
        {
            //copy all lines in file replica.c
            putc(ch, fileptr2);
        }
        if (ch == '\n')
        {
            temp++;
        }
    }
    int charsToDelete = 1;
    fseeko(fileptr2, -charsToDelete, SEEK_END);
    int position = ftello(fileptr2);
    ftruncate(fileno(fileptr2), position);
    //putc(EOF,fileptr2);
    fclose(fileptr1);
    fclose(fileptr2);
    remove(filename);
    //rename the file replica.c to original name
    rename("replica.c", filename);
}
int searchLine(char *fname, char *str)
{
    FILE *fp;
    int line_num = 1;
    int find_result = 0;
    char temp[512];

    //gcc users
    if ((fp = fopen(fname, "r")) == NULL)
    {
        return -1;
    }

    while (fgets(temp, 512, fp) != NULL)
    {
        if ((strstr(temp, str)) != NULL)
        {
            printf("A match found on line: %d\n", line_num);
            printf("\n%s\n", temp);
            find_result = line_num;
        }
        line_num++;
    }
    //Close the file if still open.
    if (fp)
    {
        fclose(fp);
    }

    return find_result;
}

int main()
{
    struct sockaddr_in server; // structura folosita de server
    struct sockaddr_in from;
    char msg[100];           //mesajul primit de la client
    char msgrasp[100] = " "; //mesaj de raspuns pentru client
    int sd;                  //descriptorul de socket

    /* crearea unui socket */
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("[server]Eroare la socket().\n");
        return errno;
    }
    int reuse = 1;
    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuse, sizeof(reuse)) < 0)
        perror("setsockopt(SO_REUSEADDR) failed");

    /* pregatirea structurilor de date */
    bzero(&server, sizeof(server));
    bzero(&from, sizeof(from));

    /* umplem structura folosita de server */
    /* stabilirea familiei de socket-uri */
    server.sin_family = AF_INET;
    /* acceptam orice adresa */
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    /* utilizam un port utilizator */
    server.sin_port = htons(PORT);

    /* atasam socketul */
    if (bind(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
    {
        perror("[server]Eroare la bind().\n");
        return errno;
    }

    /* punem serverul sa asculte daca vin clienti sa se conecteze */
    if (listen(sd, 1) == -1)
    {
        perror("[server]Eroare la listen().\n");
        return errno;
    }

    /* servim in mod concurent clientii... */
    while (1)
    {
        int client;
        int length = sizeof(from);

        printf("[server]Asteptam la portul %d...\n", PORT);
        fflush(stdout);

        /* acceptam un client (stare blocanta pina la realizarea conexiunii) */
        client = accept(sd, (struct sockaddr *)&from, &length);

        /* eroare la acceptarea conexiunii de la un client */
        if (client < 0)
        {
            perror("[server]Eroare la accept().\n");
            continue;
        }

        int pid;
        if ((pid = fork()) == -1)
        {
            close(client);
            continue;
        }
        else if (pid > 0)
        {
            // parinte
            close(client);
            while (waitpid(-1, NULL, WNOHANG))
                ;
            continue;
        }
        else if (pid == 0)
        {
            // copil
            close(sd);
            char login[] = "login";
            char afisareCategorii[] = "afisare categorii";
            char afisareProduse[] = "afisare produse";
            char logout[] = "logout";
            char quit[] = "quit";
            char selectareProdus[] = "selectare produs";
            char afisareCos[] = "afisare cos";
            char stergeProdus[] = "sterge";
            char plasareComanda[] = "plasare comanda";
            int logged_status = 0;
            char *name = NULL;
            int true = 1;

            while (true)
            {
                char *server_response = NULL;
                char *login_result = NULL;
                char *logout_result = NULL;
                char *afisareCategorii_result = NULL;
                char *selectareProdus_result = NULL;
                char *plasareComanda_result = NULL;
                char *salvareCos_result = NULL;
                char *quit_result = NULL;
                char *afisareProduseCategorie_result = NULL;
                char *afisareProduse_result = NULL;
                char *afisareCos_result = NULL;
                char *stergeProdus_result = NULL;
                char *comandaInvalida = "Va rugam sa introduceti o comanda valida..";
                int lungimew = 0;
                int lungimer = 0;
                /* s-a realizat conexiunea, se astepta mesajul */
                bzero(msg, 100);
                printf("[server]Asteptam mesajul...\n");
                fflush(stdout);

                /* citirea mesajului */
                if (read(client, &lungimer, sizeof(int)) <= 0)
                {
                    perror("[client]Eroare la read() de la server,\n");
                }
                if (read(client, msg, sizeof(int) * lungimer) <= 0)
                {
                    perror("[server]Eroare la read() de la client.\n");
                    close(client); /* inchidem conexiunea cu clientul */
                                   //continue;		/* continuam sa ascultam */
                    exit(2);
                }

                server_response = comandaInvalida;
                printf("[server]Mesajul a fost receptionat...%s\n", msg);
                //parsam mesajul  - primul nume e pentru a loga
                if (strstr(msg, login))
                {
                    printf("[server]Am ajuns in login.\n");
                    if (logged_status == 1)
                        login_result = "Sunteti deja logat, pentru a va loga cu alt cont, utilizati comanda logout.";
                    else
                    {
                        login_result = loginf(msg + 6);
                        if (strcmp(login_result, "Logarea a avut loc cu succes.") == 0)
                        {
                            logged_status = 1;
                            name = getName(msg + 6);
                            printf("[server]Numele clientului logat este: %s.\n", name);
                        }
                    }

                    printf("[server]Rezultatul functiei login este : %s\n", login_result);
                    server_response = login_result;
                }
                else
                {
                    if (strstr(msg, logout))
                    {

                        printf("[server]Am ajuns in logout.\n");
                        if (logged_status == 0)
                            logout_result = "Delogarea nu se poate efectua, deoarece nu sunteti logat.\n";
                        else
                        {
                            logout_result = "V-ati delogat cu succes.\n";
                            logged_status = 0;
                            name = NULL;
                        }

                        server_response = logout_result;
                    }
                    else
                    {
                        if (strstr(msg, afisareCategorii))
                        {
                            printf("[server]Am ajuns in functia afisare categorii\n");
                            if (logged_status == 0)
                                afisareCategorii_result = "Imi pare rau, dar nu puteti efectua aceasta comanda fara sa va logati.\n";
                            else
                            {
                                /* code */
                                afisareCategorii_result = "Puteti alege produse din urmatoarele categorii :\n 1.parfumuri \n 2.machiaj\n 3.par \n 4.ten\n";
                            }
                            server_response = afisareCategorii_result;
                        }
                        else
                        {
                            if (strstr(msg, afisareProduse))
                            {
                                if (logged_status == 0)
                                    afisareProduse_result = "Imi pare rau, dar nu puteti efectua aceasta comanda fara sa va logati.\n";
                                else
                                {
                                    msg[strlen(msg) - 1] = 0;
                                    printf("[server]Am ajuns in functia de afisare produse.\n");
                                    afisareProduse_result = afisareProduseF();
                                }
                                server_response = afisareProduse_result;
                                printf("[server]Rezultatul functiei de afisare este:%s", server_response);
                            }
                            else
                            {
                                if (strstr(msg, selectareProdus))
                                {
                                    if (logged_status == 0)
                                        selectareProdus_result = "Imi pare rau, dar nu puteti efectua aceasta comanda fara sa va logati.\n";
                                    else
                                    {
                                        msg[strlen(msg) - 1] = 0;
                                        printf("[server]Am ajuns in functia de selectare produs.\n");
                                        selectareProdus_result = selectareProdusF(msg + 16, name);
                                    }
                                    server_response = selectareProdus_result;
                                }
                                else
                                {
                                    if (strstr(msg, plasareComanda))
                                    {
                                        if (logged_status == 0)
                                            plasareComanda_result = "Imi pare rau, dar nu puteti efectua aceasta comanda fara sa va logati.\n";
                                        else
                                        {
                                            msg[strlen(msg) - 1] = 0;
                                            printf("[server]Am ajuns in functia de plasare comanda.\n");
                                            plasareComanda_result = plasareComandaF(name);
                                        }
                                        server_response = plasareComanda_result;
                                    }
                                    else
                                    {
                                        if (strstr(msg, quit))
                                        {
                                            printf("[server]Am ajuns in functia quit.\n");
                                            quit_result = "Aplicatia a fost inchisa cu succes.";
                                            server_response = quit_result;

                                            // bzero(msgrasp, 100);
                                            // strcat(msgrasp, server_response);
                                            logged_status = 0;
                                            printf("[server]Trimitem mesajul inapoi...%s\n", server_response);

                                            /* returnam mesajul clientului */
                                            lungimew = strlen(server_response);
                                            if (write(client, &lungimew, sizeof(int)) <= 0)
                                            {
                                                perror("[server]Eroare la write() catre client.\n");
                                            }
                                            if (write(client, server_response, sizeof(int) * lungimew) <= 0)
                                            {
                                                perror("[server]Eroare la write() catre client.\n");
                                                //continue;
                                                /* continuam sa ascultam */
                                                //close(client);
                                                //exit(2);
                                            }
                                            else
                                                printf("[server]Mesajul a fost trasmis cu succes.\n");
                                            true = 0;
                                        }
                                        else
                                        {
                                            if (strstr(msg, afisareCos))
                                            {
                                                if (logged_status == 0)
                                                    afisareCos_result = "Imi pare rau, dar nu puteti efectua aceasta comanda fara sa va logati.\n";
                                                else
                                                {
                                                    msg[strlen(msg) - 1] = 0;
                                                    printf("[server]Am ajuns in functia de afisare cos de cumparaturi.\n");
                                                    afisareCos_result = afisareCosF(name);
                                                }
                                                server_response = afisareCos_result;
                                            }

                                            else
                                            {
                                                if (strstr(msg, "afisare parfumuri") || strstr(msg, "afisare machiaj") || strstr(msg, "afisare par") || strstr(msg, "afisare ten"))
                                                {
                                                    if (logged_status == 0)
                                                        afisareProduseCategorie_result = "Imi pare rau, dar nu puteti efectua aceasta comanda fara sa va logati.\n";
                                                    else
                                                    {
                                                        msg[strlen(msg) - 1] = 0;
                                                        printf("[server]Am ajuns in functia de afisare produse dintr-o anumita categorie.\n");
                                                        afisareProduseCategorie_result = afisare(msg + 8);
                                                    }
                                                    server_response = afisareProduseCategorie_result;
                                                    printf("[server]Rezultatul functiei de afisare este:%s", server_response);
                                                }
                                                else
                                                {
                                                    if (strstr(msg, stergeProdus))
                                                    {
                                                        if (logged_status == 0)
                                                            stergeProdus_result = "Imi pare rau, dar nu puteti efectua aceasta comanda fara sa va logati.\n";

                                                        else
                                                        {
                                                            msg[strlen(msg) - 1] = 0;
                                                            printf("[server]Am ajuns in functia de stergere produs.\n");
                                                            printf("[server]Numele utilizatorului curent este:%s.\n", name);
                                                            stergeProdus_result = stergereProdusF(msg + 7, name);
                                                        }
                                                        server_response = stergeProdus_result;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                /*pregatim mesajul de raspuns */
                // bzero(msgrasp, 100);
                // strcat(msgrasp, server_response);

                printf("%s[server]Trimitem mesajul inapoi...%s\n", KMAG, server_response);

                /* returnam mesajul clientului */
                lungimew = strlen(server_response);
                if (write(client, &lungimew, sizeof(int)) <= 0)
                {
                    perror("[server]Eroare la write() catre client.\n");
                }
                if (write(client, server_response, sizeof(int) * lungimew) <= 0)
                {
                    perror("[server]Eroare la write() catre client.\n");
                    //continue;
                    /* continuam sa ascultam */
                    //close(client);
                    //exit(2);
                }
                else
                    printf("[server]Mesajul a fost trasmis cu succes.\n");
            }
            /* am terminat cu acest client, inchidem conexiunea */
            logged_status = 0;
            close(client);
            exit(0);
        }

    } /* while */
} /* main */