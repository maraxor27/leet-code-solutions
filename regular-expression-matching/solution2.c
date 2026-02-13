#include <stdio.h>

#define MAX_PATTERN 20

typedef enum {
    Fix,
    Unknown
} Quantity;

typedef struct {
    Quantity q;
    unsigned char min;
    char c;
} RegexPattern;

typedef struct {
    unsigned int length;
    RegexPattern unit[0];
} Regex;

Regex* parsePattern(char* pattern) {
    Regex* regex = malloc(sizeof(Regex) + sizeof(RegexPattern) * MAX_PATTERN);
    printf("Allocated\n");
    unsigned int pattern_index = 0;
    for (char* hand = pattern; *hand != 0; hand++) {
        char c = *hand;
        switch (c) {
            case '*':
                if (*(hand-1) == '*')  
                printf("hit *\n");
                regex->unit[pattern_index-1].q = Unknown;
                regex->unit[pattern_index-1].min -= 1;
                break;
            default:
                if (pattern_index > 0 && regex->unit[pattern_index-1].c == c) {
                    printf("Same as previous. Incrementing min on current pattern\n");
                    regex->unit[pattern_index-1].min += 1;
                } else {
                    printf("New Pattern\n");
                    regex->unit[pattern_index].q = Fix;
                    regex->unit[pattern_index].min = 1;
                    regex->unit[pattern_index].c = c;
                    pattern_index++;
                }
                break;
        }
    }
    regex->length = pattern_index;

    return regex;
}

int patternMatch(RegexPattern pattern, char* c) {
    switch (pattern.c) {
        case '.': 
            return *c != 0;
        default:
            return pattern.c == *c;
    }
}

int recursiveMatching(Regex* regex, char* hand, unsigned int pattern_index) {
    while (pattern_index < regex->length) {
        RegexPattern pattern = regex->unit[pattern_index];
        unsigned char counter = 0;
        while (patternMatch(pattern, hand) && counter < pattern.min) {
            hand++;
            counter++;
        }
        if (counter != pattern.min) {
            return 0;
        }
        if (pattern.q == Unknown) {
            while (patternMatch(pattern, hand)) {
                if (recursiveMatching(regex, hand, pattern_index+1)) {
                    return 1;
                }
                hand++;
            }
        }
        pattern_index++;
    }

    return *hand == 0 && pattern_index == regex->length;
}

int isMatch(char* string, char* pattern) {
    Regex* regex = parsePattern(pattern);
    printf("Half way!\n");
    return recursiveMatching(regex, string, 0);
}