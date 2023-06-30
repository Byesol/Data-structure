#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 10000001
#define MAX_PATTERN_SIZE 100000
char string[MAX_STRING_SIZE];
char pattern[MAX_PATTERN_SIZE];
int positions[MAX_STRING_SIZE] = { 0 };

void naive(char* str, int n, char* pat, int m) {
    int count = 0;    
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (str[i + j] != pat[j])
                break;
        }
        if (j == m) {
            positions[count++] = i;
        }
    }
    FILE* fp;
    fp = fopen("result_naive.txt", "w");
    if (fp == NULL) {
        printf("File open error!\n");
        exit(1);
    }
    fprintf(fp, "%d\n", count);
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d ", positions[i]);
    }
    fprintf(fp, "\n");
    fclose(fp);
}

int main() {  

    FILE* fp_string = fopen("string.txt", "r");
    if (fp_string == NULL) {
        printf("The string file does not exist.\n");
        return 0;
    }
    fgets(string, sizeof(string), fp_string);
    fclose(fp_string);

    FILE* fp_pattern = fopen("pattern.txt", "r");
    if (fp_pattern == NULL) {
        printf("The pattern file does not exist.\n");
        return 0;
    }
    fgets(pattern, sizeof(pattern), fp_pattern);
    fclose(fp_pattern);

    int n = strlen(string);
    int m = strlen(pattern);

    if (string[n - 1] == '\n') {
        string[n - 1] = '\0';
        n--;
    }
    if (pattern[m - 1] == '\n') {
        pattern[m - 1] = '\0';
        m--;
    }

    naive(string, n, pattern, m);

    return 0;
}
