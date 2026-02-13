// Better than 42% on speed 
#include <stdlib.h>

int isPalindrome(char* buffer, int start, int end) {
    while(start < end && buffer[start] == buffer[end]) {
        printf("t: (%d, %d)\n", start, end);
        start++;
        end--;
    }
    return start >= end;
}

char* longestPalindrome(char* s) {
    int len = strlen(s);
    int best_start = 0, best_end = 0, best_len = 0;
    for (int i = 0; i < len; i++) {
        for (int j = len - 1; j >= i + best_len; j--) {
            if (isPalindrome(s, i, j)) {
                printf("Good: (%d, %d)\n", i, j);
                best_start = i;
                best_end = j;
                best_len = j - i;
                break;
            } else {
                printf("Bad: (%d, %d)\n", i, j);
            }
        }
    }
    s[best_end+1] = '\0';
    printf("\"%s\"", s + best_start);
    return s + best_start;
}