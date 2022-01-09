#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#define lungime_max 300

#define UT_NAMESIZE 32
#define UT_HOSTSIZE 256
// struct
// {
//     int32_t tv_sec;
//     int32_t tv_usec;
// } ut_tv;

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

char *getClientInfo(struct client_info *client)
{
    char info[3000];
    char *username = getUsername(&client);
    printf("%s", &username);
    char *hostname = getHostName(&client);
    struct tm *tm = getTimeEntry(&client);
    strncpy(info, username, strlen(username));
    strncat(info, " ", 1);
    strncat(info, hostname, strlen(hostname));
    strncat(info, " ", 1);
    strncat(info, asctime(tm), strlen(asctime(tm)));
    printf("%s", info);
    return *info;
}

//name, state, ppid, uid, vmsize)
//despre procesul indicat (sursa informatii: fisierul /proc/<pid>/status)

struct proc_info
{
    char name[UT_NAMESIZE];
    char state[UT_NAMESIZE];
    pid_t p_pid;
    pid_t uid;
    int vmsize;
};

void setProcessInfo(pid_t pid, struct proc_info *proc)
{
    proc->p_pid = getppid();
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
        if (given_username[i] != ' ')
        {
            username1[j] = given_username[i];
        }
        else
        {
            j--;
        }
    username1[j] = 0;

    printf("%s", username1);

    if ((folder = fopen("useri.ini", "r")) < 0)
        perror("Eroare la citirea din fisier");

    if (folder == NULL)
        perror("Eroare, fisier inexistent..");

    fflush(stdout);
    while (fgets(username, lungime_max, folder) != NULL)
    {

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

        printf("%s", username);

        if (strcmp(username1, username2) == 0)

        {
            found = 1;
            break;
        }
    }
    if (found == 1)
        strcpy(result, "Logarea a avut loc cu succes!");
    else
    {
        strcpy(result, "Username-ul dvs. nu apare in baza noastra de date.\n");
    }

    return result;
}

void getProcInfo(char pid[100])
{   char path[100];
    strcpy(path,"/proc/");
    strcat(path,pid);
    strcat(path,"/status");
    printf("%s\n",path);
    char arr1 [lungime_max];
    int fd;
    char *myfifo = path;
    if ((fd = open(myfifo, O_RDONLY)) < 0)
        perror("Can't open it..");

    if (read(fd, arr1, lungime_max) < 0)
        perror("Error, can't read..");
    printf("%s", arr1);
}

int main(void)
{
    // struct client_info client;
    // setClientInfo("Roxana", &client);
    // char *username = getUsername(&client);
    // char *hostname = getHostName(&client);
    // struct tm *tm = getTimeEntry(&client);
    // // printf("Username:%s\n", username);
    // // printf("Hostname:%s\n", hostname);
    // // printf("Current local time and date: %s", asctime(tm));
    // char info[3000];
    // strncpy(info, username, strlen(username));
    // strncat(info, " ", 1);
    // strncat(info, hostname, strlen(hostname));
    // strncat(info, " ", 1);
    // strncat(info, asctime(tm), strlen(asctime(tm)));
    // // //char * info = getClientInfo(&client);
    // // printf("%s" , getClientInfo(&client));
    //printf("%s", info);
    //fflush(stdout);
    //char *answer = loginf("roxana");
    //printf("%s", answer);
    getProcInfo("2287");
    return EXIT_SUCCESS;
}