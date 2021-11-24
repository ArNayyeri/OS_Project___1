#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

long long int size(char text[])
{
    long long int n = 0;
    for (long long int i = 0; text[i] != '\0'; i++)
        if (text[i] == '$')
            n++;
    return n;
}

void setWord(char word[], char decode[], long long int a, long long int b)
{
    for (int i = a; i < a + b; i++)
        word[i - a] = decode[i];
    word[a + b] = '\0';
}

void sentFile(char text[10000], char word[1000][1000], long long int n)
{
    for (long long int i = 0, a = 0; i < n; ++i)
    {
        for (long int j = 0; word[i][j] != '\0'; ++j)
            text[a++] = word[i][j];
        text[a++] = '#';
        text[a] = '\0';
    }
}

long long int find(char decode[], char text[], char word[1000][1000])
{
    long long int S = size(text), j = 0;
    for (long long int i = 0, a = 0, b = 0, c = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '$')
        {
            setWord(word[j++], decode, a, b);
            a = 0;
            b = 0;
        }
        else if (text[i] == ' ')
            c = (c == 0) ? 1 : 0;
        else
        {
            if (c == 0)
                a = a * 10 + (text[i] - '0');
            else
                b = b * 10 + (text[i] - '0');
        }
    }
    FILE* fp;
    fp = fopen("Finder Text.txt", "w");
    for (long long int i = 0; i < S; i++)
    {
        fprintf(fp, "%s\n", word[i]);
    }
    fclose(fp);
    return j;
}

int main()
{
    char decode[10000], text[10000], word[1000][1000];

    mkfifo("myfifoAB", 0777);
    int fd = open("myfifoAB", O_RDONLY);
    read(fd, decode, sizeof(decode));
    close(fd);

    mkfifo("myfifoB", 0777);
    fd = open("myfifoB", O_RDONLY);
    read(fd, text, sizeof(text));
    close(fd);

    long long int n = find(decode, text, word);

    sentFile(text, word, n);

    mkfifo("myfifoBC", 0777);
    fd = open("myfifoBC", O_WRONLY);
    write(fd, text, strlen(text));

    close(fd);
    return 0;
}