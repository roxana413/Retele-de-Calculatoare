#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#define lungime_max 300

int main()
{
    int fd;
    int ON = 1;
    char *myfifo = "/home/roxana/Desktop/Tema1/myfifo";
    if (mkfifo(myfifo, 0666) < 0)
    perror("Can't make that fifo");

    char arr1[lungime_max] = "", arr2[lungime_max] = "";

    while (ON)
    {
        if ((fd = open(myfifo, O_WRONLY)) < 0)
            perror("Can't open it..");

        if (fgets(arr2, lungime_max, stdin) < 0)
            perror("Eroare la citire de la stdin");
     
        if (write(fd, arr2, lungime_max) < 0)
            perror("Can't write..");
        close(fd);

        if ((fd = open(myfifo, O_RDONLY)) < 0)
            perror("Can't open it..");

        if (read(fd, arr1, lungime_max) < 0)
            perror("Error, can't read..");
        if (!strcmp(arr1,"quit"))
        {
            printf("Clientul se inchide...");
            close(fd);
            ON = 0;
            
        }

        printf("Server response: %s\n", arr1);

        close(fd);
    }

    return 0;
}