#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

char changeLetter(char c) {
    if ((c <= 'Z' && c >= 'X') || (c <= 'z' && c >= 'x'))
        return c - 23;
    return c + 3;
}

void decode(char text[]) {
    for (long long int i = 0; text[i] != '\0'; i++)
        if (text[i] != ' ' && text[i] != '\n')
            text[i] = changeLetter(text[i]);
    FILE *fp;
    fp = fopen("Decode Text.txt", "w");
    fprintf(fp, "%s", text);
    fclose(fp);
}

int main() {
    mkfifo("myfifoA", 0777);
    int fd = open("myfifoA", O_RDONLY);
    char text[10000];
    read(fd, text, sizeof(text));
    close(fd);


    decode(text);


    mkfifo("myfifoAB", 0777);
    fd = open("myfifoAB", O_WRONLY);
    write(fd, text, strlen(text));
    close(fd);


    return 0;
}