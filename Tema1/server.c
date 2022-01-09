#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#define UT_LINESIZE 32
#define UT_NAMESIZE 32
#define UT_HOSTSIZE 256
#define lungime_max 300

struct
{
    int32_t tv_sec;
    int32_t tv_usec;
} ut_tv;

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
        //printf("%s", "Sunt aici");
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

        //printf("%s", username);

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
}
struct client_info
{
    struct tm tm;
    char hostname[UT_HOSTSIZE];
    char username[UT_NAMESIZE];
};

void setClientInfo(char username[], struct client_info *client)
{
    strcpy(client->username, username);
    gethostname(client->hostname, UT_HOSTSIZE);
    time_t T = time(NULL);
    client->tm = *localtime(&T);
}
char *getUsername(struct client_info *client)
{
    return client->username;
}

char *getHostName(struct client_info *client)
{
    return client->hostname;
}

struct tm *getTimeEntry(struct client_info *client)
{
    return &client->tm;
}

char *getProcInformation(char pid[100])
{

    char pid2[lungime_max];
    strncpy(pid2, pid, 4);
    pid2[4] = 0;
    // int i,j;
    // for (i = 0, j = 0; i < strlen(pid); i++, j++)
    //     if (pid[i] != '\n')
    //     {
    //         pid2[j] = pid[i];
    //     }
    //     else
    //     {
    //         j--;
    //     }

    //pid2[j]=0;

    char path[100];
    strcpy(path, "/proc/");
    strcat(path, pid2);
    strcat(path, "/status");
    printf("Path :%s\n", path);
    char *arr1 = malloc(lungime_max);
    int fd;
    char *myfifo = path;
    if ((fd = open(myfifo, O_RDONLY)) < 0)
        perror("Can't open it..");

    if (read(fd, arr1, lungime_max) < 0)
        perror("Error, can't read..");
    printf("%s", arr1);
    return arr1;
}

void getLoggedUsers()
{
    char user[UT_NAMESIZE];
    char host[UT_HOSTSIZE];
    struct timeval ut_tv;
    gethostname(host, UT_HOSTSIZE);
}
struct client_info client;

int main()
{

    char log[1] = "1";
    int ON = 1;
    int fd1, fd3, fd4;
    pid_t pid1, pid2, pid3;
    int semnal1 = 0, semnal2 = 0, semnal3 = 0;
    char *myfifo = "/home/roxana/Desktop/Tema1/myfifo";
    char *myfifo2 = "/home/roxana/Desktop/Tema1/myfifo2";
    char *myfifo3 = "/home/roxana/Desktop/Tema1/myfifo3";
    char login[] = "login";
    char getLoggedUsers[] = "get-logged-users";
    char getProcInfo[] = "get-proc-info";
    char logout[] = "logout";
    char quit[] = "quittt";
    int fd[2], fd2[2];
    pid_t pid;
    int any = 0;
    int p1[2]; //initializam primul pipe
    int p2[2];
    int p3[2];
    int p4[2];
   
    // if (mkfifo(myfifo, 0666) < 0)
    //  perror("Can't create it..");
    // if (mkfifo(myfifo2, 0666) < 0)
    //  perror("Can't create it..");
    // if (mkfifo(myfifo3, 0666) < 0)
    //     perror("Can't create it..");
    //scrie log in fd4 ca fiind 0 -- nimeni nu s-a logat
    // if ((fd4 = open(myfifo3, O_WRONLY)) < 0)
    //     perror("Error while opening.. ");
    // if (write(fd4, log, 1) < 0)
    //     perror("Error, can't write");
    // close(fd4);

    while (ON)
    {
        // if ((fd4 = open(myfifo3, O_RDONLY)) < 0)
        //     perror("Error while opening..");

        // if (read(fd4, log, 1) < 0)
        //     perror("Error, can't read");
        any = 0;
        if (socketpair(PF_LOCAL, SOCK_STREAM, 0, fd) == -1)
            perror("Error while creating socketpair..");
        if (socketpair(PF_LOCAL, SOCK_STREAM, 0, fd2) == -1)
            perror("Error while creating socketpair..");

        if (pipe(p3) == -1)
        {
            perror("Error, can't make pipe..");
        }
        if (pipe(p1) == -1)
        {
            perror("Error, can't make pipe..");
        }
        if (pipe(p2) == -1)
        {
            perror("Error, can't make pipe..");
        }
        if (pipe(p4) == -1)
        {
            perror("Error, can't make pipe..");
        }
        
        char str1[lungime_max] = {};
        char str2[lungime_max] = {};
     
        if ((fd1 = open(myfifo, O_RDONLY)) < 0)
            perror("Error while opening..");

        if (read(fd1, str1,lungime_max) < 0)
            perror("Error, can't read");

        printf("Client request: %s\n", str1);
        close(fd1);

        //verificam tipul comenzii
        if (strstr(str1, login) && str1 != NULL) //&& strcmp(log,"0"))
        {
            any = 1;
            strcpy(log, "1");

            pid1 = fork();

            if (pid1 == -1)
            {
                perror("Error, can't make a child process..");
                exit(1);
            }
            if (pid1)
            {
                any = 1;
                printf("Sunt la procesarea comenzii login..\n");
                char result[lungime_max];
                close(p1[0]); //transmitem prima comanda catre fiu
                if (write(p1[1], str1, lungime_max) < 0)
                    perror("Error while writing...");
                close(p1[1]);

                //asteptam ca copilul sa returneaze
                wait(&semnal1);

                close(p3[1]);
                if (read(p3[0], result, lungime_max) < 0)
                    perror("Error reading from pipe...");
                close(p3[0]);
                //cream un canal de comunicare cu primul copil care va prelucra comanda login
                //apoi primim rezultatul si il transmitem inapoi la client
                printf("%s", result);
                strcpy(str2, result);
            }
            else
            { //citim din pipe
                char command[lungime_max];
                close(p1[1]);
                if ((read(p1[0], command, lungime_max)) < 0)
                    perror("Error while reading from pipe..");
                printf("Am ajuns in primul proces copil\n");
                close(p1[0]);
                //
                printf("Comanda preluata de la procesul tata: %s", command);
                //procesam username pt a putea apela functia login
                strncpy(command, command + 8, 10);
                printf("Username cu care se va apela: %s", command);

                //apelam functia login
                char *result_l = NULL;

                result_l = loginf(command);
                if (strcmp(result_l, "Logarea a avut loc cu succes.") == 0)
                {
                    log[0] = "1";
                    //logam clientul
                    //modificam in myfifo3 statusul lui log
                    // if ((fd4 = open(myfifo3, O_WRONLY)) < 0)
                    //     perror("Error while opening.. ");
                    // if (write(fd4, log, 1) < 0)
                    //     perror("Error, can't write");
                    // close(fd4);

                    setClientInfo(&command, &client);

                    char *username = getUsername(&client);
                    char *hostname = getHostName(&client);
                    struct tm *tm = getTimeEntry(&client);
                    char info[3000];
                    strncpy(info, username, strlen(username));
                    strncat(info, " ", 1);
                    strncat(info, hostname, strlen(hostname));
                    strncat(info, " ", 1);
                    strncat(info, asctime(tm), strlen(asctime(tm)));

                    char answer[lungime_max];
                    strcpy(answer, info);
                    printf("Rezultatul functiei get-proc-info: %s", answer);

                    // if ((fd3 = open(myfifo2, O_WRONLY)) < 0)
                    //     perror("Error while opening.. ");
                    // if (write(fd3, answer, lungime_max) < 0)
                    //     perror("Error, can't write");
                    // close(fd3);
                }

                //log = 1;

                printf("Rezultatul functiei login:%s\n", result_l);

                //scriem in pipe
                close(p3[0]);
                if ((write(p3[1], result_l, lungime_max)) < 0)
                    perror("Error while writing in pipe..");

                any = 1;
                close(p3[1]);

                semnal1 = 1;
                exit(semnal1);
            }
        }
        //citim status-ul de logare
        // if ((fd4 = open(myfifo3, O_RDONLY)) < 0)
        //     perror("Error while opening.. ");
        // if (read(fd4, log, 1) < 0)
        //     perror("Error, can't read");
        // close(fd4);

        // if (strstr(str1, quit))
        // {
        //     //printf("%s", "Sunt in quit");
        //     any = 1;
        //     printf("Serverul se inchide...");
        //     strcpy(str2, "0");
        //     if ((fd1 = open(myfifo, O_WRONLY)) < 0)
        //         perror("Error while opening.. ");
        //     if (write(fd1, str2, lungime_max) < 0)
        //         perror("Error, can't write");
        //     close(fd1);
        //     //goto final;
        //     ON = 0;
        // }
        if (strstr(str1,quit))
        {
            printf("%s", "Sunt in quit");
            printf("%s", str1);
            any = 1;
            printf("Serverul se inchide...");
            strcpy(str2, "quit");
            if ((fd1 = open(myfifo, O_WRONLY)) < 0)
                perror("Error while opening.. ");
            if (write(fd1, str2, lungime_max) < 0)
                perror("Error, can't write");
            close(fd1);
            ON = 0;
        }

        if (strstr(str1, logout)) //&& strcmp(log, "1"))
        {
            log[0] = "0";
            any = 1;
            strcpy(str2, "V-ati deconectat cu succes");
            // if ((fd4 = open(myfifo3, O_WRONLY)) < 0)
            //     perror("Error while opening.. ");
            // if (write(fd4, log, 1) < 0)
            //     perror("Error, can't read");
            // close(fd4);

            goto final;
        }

        if (strstr(str1, getLoggedUsers)) //&& strcmp(log, "1"))
        {

            any = 1;
            pid2 = fork();
            if (pid2 == -1)
            {
                perror("Error, can't make a child process..");
                exit(1);
            }

            if (pid2)
            {

                close(fd[0]);
                if (write(fd[1], str1, lungime_max) < 0)
                    perror("[parinte] ERR..sock write");
                close(fd[1]);

                wait(&semnal2);

                close(fd2[0]);
                if (read(fd2[1], str2, lungime_max) < 0)
                    perror("[parinte] ERR..sock read");
                close(fd2[1]);
            }
            else
            {
                char command[lungime_max];
                char answer[lungime_max] = {};
                close(fd[1]);
                if (read(fd[0], command, lungime_max) < 0)
                    perror("[copil] ERR..sock read");
                close(fd[0]);
                //citim din fifo3
                char info[lungime_max] = {};
                // if ((fd3 = open(myfifo2, O_RDONLY)) < 0)
                //     perror("Error while opening.. ");
                // if (read(fd3, info, lungime_max) < 0)
                //     perror("Error, can't read");
                // close(fd3);

                setClientInfo("roxana", &client);

                char *username = getUsername(&client);
                char *hostname = getHostName(&client);
                struct tm *tm = getTimeEntry(&client);

                strncpy(info, username, strlen(username));
                strncat(info, " ", 1);
                strncat(info, hostname, strlen(hostname));
                strncat(info, " ", 1);
                strncat(info, asctime(tm), strlen(asctime(tm)));

                // char answer[lungime_max];
                // strcpy(answer, info);

                //strcpy(answer, info);
                printf("Rezultatul functiei get-logged-users: %s", info);

                close(fd2[1]);
                if (write(fd2[0], info, lungime_max) < 0)
                    perror("[copil] ERR..sock write");
                close(fd2[0]);
                semnal2 = 1;
                exit(semnal2);
            }
        }
        else
        {
            if (strstr(str1, getLoggedUsers) && strcmp(log, "0"))
            {
                strcpy(str2, "Va rugam sa va logati pentru a putea executa aceasta comanda");
            }
        }

        if (strstr(str1, getProcInfo)) //&& strcmp(log,"1"))
        {
            any = 1;
            pid3 = fork();
            if (pid2 == -1)
            {
                perror("Error, can't make a child process..");
                exit(1);
            }

            if (pid3)
            {
                //parinte

                printf("Sunt la procesarea comenzii getProcInfo..\n");
                char result[lungime_max] = {};
                close(p2[0]); //transmitem prima comanda catre fiu
                if ((write(p2[1], str1, lungime_max)) < 0)
                    perror("Error while writing...");
                close(p2[1]);

                //asteptam ca copilul sa returneaze
                wait(&semnal3);

                close(p4[1]);
                if (read(p4[0], result, lungime_max) < 0)
                    perror("Error reading from pipe...");
                close(p4[0]);
                //cream un canal de comunicare cu primul copil care va prelucra comanda login
                //apoi primim rezultatul si il transmitem inapoi la client
                strcpy(str2, result);
            }
            else
            {
                char command[lungime_max];
                close(p2[1]);
                if ((read(p2[0], command, lungime_max)) < 0)
                    perror("Error while reading from pipe..");
                printf("Am ajuns in primul proces copil\n");
                close(p2[0]);
                //
                printf("Comanda preluata de la procesul tata: %s", command);
                //strncpy(command, command + 16, 4);

                command[strlen(command)] = '\0';
                strncpy(command, command + 16, strlen(command));
                printf("PIIIDDD:%s:", command);
                command[strlen(command)] = '\0';
                printf("Pid cu care se va apela: %s", command);
                printf("Lungime command : %d", strlen(command));
                // char command2[lungime_max];
                // int i,j;
                // for (i = 0, j = 0; i < strlen(command); i++, j++)
                //     if (command[i] != '\n')
                //     {
                //         command2[j] = command[i];
                //     }
                //     else
                //     {
                //         j--;
                //     }

                // command2[j]=0;
                //apelam functia getProcInfo
                char *result = NULL;

                result = getProcInformation(command);

                printf("Rezultatul functiei getProcInfo:%s", result);

                //scriem in pipe
                close(p4[0]);
                if ((write(p4[1], result, lungime_max)) < 0)
                    perror("Error while writing from pipe..");

                close(p4[1]);

                semnal3 = 1;
                exit(semnal3);
            }
        }
        else
        {
            if (strstr(str1, getProcInfo) && strcmp(log, "0"))
            {
                strcpy(str2, "Va rugam sa va logati pentru a putea executa aceasta comanda");
            }
        }

        if (any == 0)
        {
            strcpy(str2, "Va rugam incercati o comanda valida.");
        }
    final:
        //printf("%s", str2);
        if ((fd1 = open(myfifo, O_WRONLY)) < 0)
            perror("Error while opening.. ");
        if (write(fd1, str2, lungime_max) < 0)
            perror("Error, can't write");
        close(fd1);

    }

    return 0;
}
