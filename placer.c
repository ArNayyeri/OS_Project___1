#include <stdio.h>

void replace(char word[], char text[], int a) {
    text[a] = word[0];
    for (int i = 1; word[i] != '\0'; i++) {
        char x = word[i];
        int j;
        for (j = a + i; text[j] != '\0'; j++) {
            char c = x;
            x = text[j];
            text[j] = c;
        }
        text[j] = x;
    }
}

void place(char finder[1000][1000], char text[]) {
    for (long long int i = 0, j = 0; text[i] != '\0'; i++)
        if (text[i] == '$')
            replace(finder[j++], text, i);
    FILE *fp;
    fp = fopen("Placer Text.txt", "w");
    fprintf(fp, "%s", text);
    fclose(fp);
}
