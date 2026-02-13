#define DEBUG 1

#if DEBUG
#include <stdio.h>
#endif


#define BITMAP_GET(bitmap, index) (((unsigned char*) bitmap)[index / 8] & (1 << (index % 8)))
#define BITMAP_SET(bitmap, index) ((unsigned char*) bitmap)[index / 8] |= (1 << (index % 8))
#define BITMAP_CLEAR(bitmap, index) ((unsigned char*) bitmap)[index / 8] &= ~(1 << (index % 8))

int lengthOfLongestSubstring(char* s) {
    unsigned int bitmap[3] = {0, 0, 0}; // 3 * 32 = 96 
    
    #if DEBUG
    printf("sizeof(int): %ld\n", sizeof(int));
    BITMAP_SET(bitmap, 0);
    printf("bitmap: %016x\n", bitmap[0]);
    printf("found: %d\n", !!BITMAP_GET(bitmap, 0));
    #endif
    
    unsigned int s_len = 0;
    
    while (s[s_len] != 0) { s_len++; } // find strlen

    #if DEBUG
    printf("s_len: %d\n", s_len);
    #endif

    unsigned int start = 0, end = 0, best = 0, current;
    char end_c, start_c;
    while(end < s_len) {
        end_c = s[end++] - 32;
        #if DEBUG
        printf("end_c: %x\n", end_c);
        printf("bitmap: [0x%016x, 0x%016x, 0x%016x]\n", bitmap[0], bitmap[1], bitmap[2]);
        printf("(%d, %d)\n", start, end);
        printf("not found: %d\n", ! BITMAP_GET(bitmap, end_c));
        #endif

        if (! BITMAP_GET(bitmap, end_c)) {
            #if DEBUG
            printf("new char\n");
            #endif
            BITMAP_SET(bitmap, end_c);
        } else {
            #if DEBUG
            printf("seen char\n");
            #endif
            while (1) {
                start_c = s[start++] - 32;
                if (start_c != end_c) {
                    BITMAP_CLEAR(bitmap, start_c);
                } else {
                    break;
                }
            }
        }

        current = end - start;
        if (best < current) {
            best = current;
        }
        #if DEBUG
        fflush(stdout);
        #endif
    }
    return best;
}