#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_SIZE 10000001

char string[MAX_STRING_SIZE];
         
char pattern[MAX_STRING_SIZE];
int pi[MAX_STRING_SIZE];
int match[MAX_STRING_SIZE];

void make_pi(char* pat, int* pi) {
    int m = strlen(pat);
    int j = 0;
    pi[0] = 0;
    for (int i = 1; i < m; i++) {
        while (j > 0 && pat[i] != pat[j]) {

            j = pi[j - 1];
        }
        if (pat[i] == pat[j]) {
            pi[i] = j + 1;
            j++;
        }
        else {
            pi[i] = 0;
        }
    }
}

void kmp_search(char* str, char* pat, int* pi, int* match, int* count) {
    int n = strlen(str);
    int m = strlen(pat);
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && str[i] != pat[j]) {
            j = pi[j - 1];
        }
        if (str[i] == pat[j]) {
            if (j == m - 1) {
                match[*count] = i - m + 1;
                (*count)++;
                j = pi[j];
            }
            else {
                j++;
            }
        }
    }
}

int main() {
    FILE* fp_str = fopen("string.txt", "r");
    FILE* fp_pat = fopen("pattern.txt", "r");
    FILE* fp_out = fopen("result_kmp.txt", "w");
    if (fp_str == NULL) {
        printf("The string file does not exist.\n");
        return 0;
    }
    if (fp_pat== NULL) {
        printf("The pattern file does not exist.\n");
        return 0;
    }
    if (fp_out == NULL) {
        printf("File open error!\n");
        exit(1);
    }
  
    int count = 0;
    fgets(string, sizeof(string), fp_str);
    fgets(pattern, sizeof(pattern), fp_pat);

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

    make_pi(pattern, pi);
    kmp_search(string, pattern, pi, match, &count);
    fprintf(fp_out, "%d\n", count);
    for (int i = 0; i < count; i++) {
        fprintf(fp_out, "%d ", match[i]);
    }
    fclose(fp_str);
    fclose(fp_pat);
    fclose(fp_out);
    return 0;
}

