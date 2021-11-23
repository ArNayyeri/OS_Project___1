#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

void replace(char word[], char text[], int a)
{
    text[a] = word[0];
    for (int i = 1; word[i] != '\0'; i++)
    {
        char x = word[i];
        int j;
        for (j = a + i; text[j] != '\0'; j++)
        {
            char c = x;
            x = text[j];
            text[j] = c;
        }
        text[j] = x;
    }
}

void place(char finder[1000][1000], char text[])
{
    for (long long int i = 0, j = 0; text[i] != '\0'; i++)
        if (text[i] == '$')
            replace(finder[j++], text, i);
    FILE *fp;
    fp = fopen("Placer Text.txt", "w");
    fprintf(fp, "%s", text);
    fclose(fp);
}

int main()
{
    char text[10000], finder[1000][1000], buff[1000];

    mkfifo("myfifoBC", 0777);
    int fd = open("myfifoBC", O_RDONLY);
    read(fd, buff, sizeof(buff));
    close(fd);

    for (long long int i = 0, j = 0, r = 0; buff[i] != '\0'; ++i)
    {
        if (buff[i] == '#')
        {
            for (int k = r; k < r + i; ++k)
            {
                finder[j][k - r] = buff[k];
            }
            finder[j++][i - r] = '\0';
            r = i + 1;
        }
    }

    mkfifo("myfifoC", 0777);
    fd = open("myfifoC", O_RDONLY);
    read(fd, text, sizeof(text));
    close(fd);

    place(finder, text);

    mkfifo("myfifoC", 0777);
    fd = open("myfifoC", O_WRONLY);
    write(fd, text, strlen(text));
    close(fd);

    return 0;
}