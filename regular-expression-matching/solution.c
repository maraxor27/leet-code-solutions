#include <stdio.h>

typedef enum {
    Single,
    Many
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
    unsigned int pattern_count = 0;
    for (char* hand = pattern; *hand != 0; hand++) {
        switch (*hand) {
            case '*':
                break;
            default:
                pattern_count++;
                break;
        }
    }

    size_t regex_size = sizeof(Regex) + sizeof(RegexPattern) * pattern_count;
    Regex* regex = malloc(regex_size);
    regex->length = pattern_count;

    unsigned int pattern_index = 0;

    for (char* hand = pattern; *hand != 0; hand++) {
        char c = *hand;
        switch (c) {
            case '*':
                regex->unit[pattern_index-1].q = Many;
                break;
            default:
                regex->unit[pattern_index].q = Single;
                regex->unit[pattern_index].c = c; 
                pattern_index++;
                break;
        }
    }
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
        if (pattern.q == Single) {
            if (patternMatch(pattern, hand)) {
                hand++;
                pattern_index++;
            } else {
                break;
            }
        } else {
            while (patternMatch(pattern, hand)) {
                if (recursiveMatching(regex, hand, pattern_index+1)) {
                    return 1;
                }
                hand++;
            }
            pattern_index++;
        }
    }

    return *hand == 0 && pattern_index == regex->length;
}

int isMatch(char* string, char* pattern) {
    Regex* regex = parsePattern(pattern);
    
    return recursiveMatching(regex, string, 0);
}