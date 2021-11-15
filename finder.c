#include <stdio.h>

long long int size(char text[]) {
    long long int n = 0;
    for (long long int i = 0; text[i] != '\0'; i++)
        if (text[i] == '$')
            n++;
    return n;
}

void setWord(char word[], char decode[], long long int a, long long int b) {
    for (int i = a; i < a + b; i++)
        word[i - a] = decode[i];
}

void find(char decode[], char text[], char word[1000][1000]) {
    long long int S = size(text);
    for (long long int i = 0, a = 0, b = 0, c = 0, j = 0; text[i] != '\0'; i++) {
        if (text[i] == '$') {
            setWord(word[j++], decode, a, b);
            a = 0;
            b = 0;
        } else if (text[i] == ' ')
            c = (c == 0) ? 1 : 0;
        else {
            if (c == 0)
                a = a * 10 + (text[i] - '0');
            else
                b = b * 10 + (text[i] - '0');
        }
    }
    FILE *fp;
    fp = fopen("Finder Text.txt", "w");
    for (long long int i = 0; i < S; i++) {
        fprintf(fp, "%s\n", word[i]);
    }
    fclose(fp);
}