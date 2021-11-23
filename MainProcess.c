#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

void stringConnect(char str[10000], char buff[1000])
{
    int i;
    for (i = 0; i < 10000; ++i)
    {
        if (str[i] == '\0')
            break;
    }
    for (int j = 0; j < 1000; ++j)
    {
        str[i + j] = buff[j];
        if (buff[j] == '\0')
            break;
    }
}

int main()
{
    int status;
    pid_t A;
    pid_t B;
    pid_t C;
    A = fork();
    if (A < 0)
    {
        printf("child process failed to create");
        return -1;
    }
    else if (A > 0)
    {
        B = fork();
        if (B < 0)
        {
            printf("child process failed to create");
            return -1;
        }
        else if (B > 0)
        {
            C = fork();
            if (C < 0)
            {
                printf("child process failed to create");
                return -1;
            }
        }
    }
    if (A == 0)
    {
        char *args[] = {"./decoder", NULL};
        execvp(args[0], args);
    }
    else if (B == 0)
    {
        char *args[] = {"./finder", NULL};
        execvp(args[0], args);
    }
    else if (C == 0)
    {
        char *args[] = {"./placer", NULL};
        execvp(args[0], args);
    }
    else
    {

        char str1[10000], str2[10000], str3[10000], buff[1000];
        str1[0] = '\0';
        str2[0] = '\0';
        str3[0] = '\0';
        FILE *fp;
        fp = fopen("Text.txt", "r");
        while (1)
        {
            fscanf(fp, "%s", buff);
            if (strcmp(buff, "###") == 0)
                break;
            stringConnect(str1, buff);
        }
        fgets(buff, 1000, (FILE *)fp);
        fgets(str2, 10000, (FILE *)fp);
        for (int i = 0; i < 10000; i++)
        {
            if (str2[i] == '\n')
            {
                str2[i] = '\0';
                break;
            }
            else if (str2[i] == '\0')
                break;
        }
        fgets(buff, 1000, (FILE *)fp);
        while (fgets(buff, 1000, fp) != NULL)
            stringConnect(str3, buff);
        for (int i = 0; i < 10000; i++)
        {
            if (str3[i] == '\n' && str3[i + 1] == '\0')
            {
                str3[i] = '\0';
                break;
            }
            else if (str3[i] == '\0')
                break;
        }
        fclose(fp);

        mkfifo("myfifoA", 0777);
        int fd = open("myfifoA", O_WRONLY);
        write(fd, str1, strlen(str1));
        close(fd);

        waitpid(A, &status, 0);

        mkfifo("myfifoB", 0777);
        fd = open("myfifoB", O_WRONLY);
        write(fd, str2, strlen(str2));
        close(fd);

        waitpid(B, &status, 0);

        mkfifo("myfifoC", 0777);
        fd = open("myfifoC", O_WRONLY);
        write(fd, str3, strlen(str3));
        close(fd);

        mkfifo("myfifoC", 0777);
        fd = open("myfifoC", O_RDONLY);
        read(fd, str1, sizeof(str1));
        close(fd);

        waitpid(C, &status, 0);

        printf("%s", str1);
    }

    return 0;
}