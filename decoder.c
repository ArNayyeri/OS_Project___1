#include <stdio.h>

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
