
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define lungime_max 300
// char *afisare(char categorie[])
// {
//     printf("[server]Am intrat in functia de afisare..\n");
//     printf("[server]Categoria aleasa:%s\n", categorie);
//     char *lista_produse = NULL;
//     FILE *folder;
//     char folder_name[15] = {};
//     char extension[] = ".txt";
//     strcpy(folder_name, categorie);
//     strcat(folder_name, extension);
//     printf("[server]Numele fisierului cautat este: %s", folder_name);
//     if ((folder = fopen(folder_name, "r")) < 0)
//         perror("Eroare la citirea din fisier");

//     if (folder == NULL)
//         perror("Eroare, fisier inexistent..");
// }
// void adaugareInCos(char produs[], char nume[])
// {
//     //cream fisierul cu numele utilizatorului
//     //adugam produsul
// }

// char *selectareProdusF(char categorie[], char nume[])
// {
//     char str[80] = {};
//     const char s[2] = " ";
//     char *token;
//     char categorie_n[20] = {};
//     int length;
//     char fname[20] = {};
//     char fname_user[20] = {};
//     char extension[] = ".txt";
//     char produs1[30] = {};
//     int found = 0;
//     char *result = malloc(lungime_max);
//     FILE *folder;

//     strcpy(str, categorie);
//     /* get the first token */
//     token = strtok(str, s);
//     length = strlen(token);

//     printf("Categoria este:%s.\n", token);
//     printf("Produsul este:%s.\n", categorie + length + 1);
//     strcpy(produs1, categorie + length + 1);
//     printf("Produsul cautat este:%s.\n", produs1);
//     //cream numele pentru cele 2 fisiere
//     memcpy(categorie_n, categorie, length);
//     strcpy(fname, categorie_n);
//     strcat(fname, extension);

//     strcpy(fname_user, nume);
//     strcat(fname_user, extension);

//     printf("[server]Numele fisierului cautat este: %s\n", fname);
//     found = searchInFile(fname, produs1);
//     //printf("%d", found);
//     if (found == 0)
//         strcpy(result, "Ne pare rau dar produsul nu exista..");

//     if (found == -1)
//         strcpy(result, "Ne pare rau dar categoria nu exista...");

//     if (found == 1)
//     {
//         //aduagam in cos
//         if ((folder = fopen(fname_user, "a")) < 0)
//             perror("Eroare la append in fisier");

//         if (folder == NULL)
//             perror("Eroare, fisier inexistent..");
//         /* Append data to file */
//         fputs(produs1, folder);
//         fputs("\n", folder);
//         fclose(folder);

//         strcpy(result, "Produsul a fost adaugat cu succes in cosul de cumparaturi..");
//     }
//     return result;
// }

// char *afisareCos(char nume[])
// {
//     char folder_name[15] = {};
//     char extension[] = ".txt";
//     long lSize;
//     char *buffer;
//     FILE *folder;

//     printf("[server]Am intrat in functia de afisare cos..\n");
//     printf("[server]Numele utilizatorului este:%s\n", nume);

//     strcpy(folder_name, nume);
//     strcat(folder_name, extension);
//     printf("[server]Numele fisierului cautat este: %s\n", folder_name);

//     if ((folder = fopen(folder_name, "r")) < 0)
//         perror("Eroare la citirea din fisier");

//     if (folder == NULL)
//         perror("Eroare, fisier inexistent..");

//     fseek(folder, 0L, SEEK_END);
//     lSize = ftell(folder);
//     rewind(folder);

//     /* allocate memory for entire content */
//     buffer = calloc(1, lSize + 1);
//     if (!buffer)
//         fclose(folder), fputs("memory alloc fails", stderr), exit(1);

//     /* copy the file into the buffer */
//     if (1 != fread(buffer, lSize, 1, folder))
//         fclose(folder), free(buffer), fputs("entire read fails", stderr), exit(1);

//     /* buffer is a string contains the whole text */

//     return buffer;

//     fclose(folder);
//     free(buffer);
// }
// char *plasareComandaF(char nume[])
// {
//     char *result;
//     //verificam daca exista cosul de cumparaturi
//     char folder_name[15] = {};
//     char extension[] = ".txt";
//     char cos[] = "cos";
//     long lSize;
//     char *buffer;
//     FILE *fptr1, *fptr2;
//     char c;
//     char cos_folder_name[20] = {};

//     printf("[server]Am intrat in functia de afisare cos..\n");
//     printf("[server]Numele utilizatorului este:%s\n", nume);

//     strcpy(folder_name, nume);
//     strcat(folder_name, extension);
//     printf("[server]Numele fisierului cautat este: %s\n", folder_name);

//     //cream un alt fisier de tipul numecos.txt
//     strcpy(cos_folder_name, nume);
//     strcat(cos_folder_name, cos);
//     strcat(cos_folder_name, extension);
//     printf("[server]Numele noului fisier care se va crea este:%s.\n", cos_folder_name);

//     if ((fptr1 = fopen(folder_name, "r")) < 0)
//         perror("Eroare la citirea din fisier");

//     if (fptr1 == NULL)
//     {
//         return "Ne pare rau, dar comanda dumneavoastra nu contine niciun articol..";
//         perror("Eroare, fisier inexistent..");
//         exit(EXIT_FAILURE);
//     }

//     //cream un alt fisier de tipul numecos.txt
//     //copiem continutul primului fisier in al 2-lea
//     //stergem primul fisier
//     // Open another file for writing
//     fptr2 = fopen(cos_folder_name, "w");
//     if (fptr2 == NULL)
//     {
//         printf("Cannot open file %s \n", cos_folder_name);
//         exit(0);
//     }

//     // Read contents from file
//     c = fgetc(fptr1);
//     while (c != EOF)
//     {
//         fputc(c, fptr2);
//         c = fgetc(fptr1);
//     }
//     printf("\nContents copied to %s", cos_folder_name);
//     fclose(fptr1);
//     fclose(fptr2);
//     // if ((fptr1 = fopen(folder_name, "w")) < 0)
//     // {
//     //     perror("Cannot delete the file %s \n");
//     //     exit(EXIT_FAILURE);
//     // }
//     // fclose(fptr1);
//     remove(folder_name);
//     return "Comanda dumnevoastra a fost plasata cu succes\n";
// }

char *stergereProdus(char produs[], char nume[])
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
        delete (folder_name, produs);
        //eliminam produsul din cos
        strcpy(result, "Produsul a fost eliminat cu succes din cosul de cumparaturi.");
    }
    else
    {
        strcpy(result, "Produsul selectat nu este in cos.");
    }

    return result;
}

void delete (char filename[], char word[])
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
    fclose(fileptr1);
    fclose(fileptr2);
    remove(filename);
    //rename the file replica.c to original name
    rename("replica.c", filename);

    return 0;
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
    if (fptr2 = fopen(cos_folder_name, "w") < 0)
        perror("Eroare la scrierea in fisier");
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
    fclose(fptr2);
    fclose(fptr1);
    if ((fptr1 = fopen(folder_name, "w")) < 0)
    {
        perror("Cannot delete the file %s \n");
        exit(EXIT_FAILURE);
    }
    fclose(fptr1);
    //remove(folder_name);
    return "Comanda dumnevoastra a fost plasata cu succes!";
}

int main()
{
    //stergereProdus("La Vie Est Belle", "produse");
    plasareComandaF("ana");
}