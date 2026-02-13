#include <stdio.h>
#include <string.h>
/*
#3
0     4     8     12
1  3  5  7  9  11 13
2     6     10    

#4
0       6       12
1    5  7    11 13
2  4    8 10    
3       9

#5
0       8           16
1     7 9        15 17
2   6   10    14    18
3 5     11 13       19 
4       12          20  
*/

int write_encoded(char* src, int src_index, char* dst, int dst_index, int length) {
    // printf("--- WRITE ---\nsrc: %p, index: %d\ndst: %p, index: %d\n\n", src, src_index, dst, dst_index);
    if (src_index < length && dst_index < length) {
        // printf("'%.1s'\n", &src[src_index]);
        dst[dst_index] = src[src_index];
        return 1;
    }
    return 0;
    
}

char* convert(char* s, int numRows) {
    size_t s_len = strlen(s);
    // printf("s_len: %d\n", s_len);
    char* encoded = alloca(s_len);
    if (numRows < 2) {
        return s;
    }
    int numColumns = s_len / (numRows * 2 - 2) + 1;
    // printf("numColumns: %d\n", numColumns);
    int step = (numRows - 1) * 2;
    // printf("step: %d\n", step); 
    int index = 0;
    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numColumns; column++) {
            if (write_encoded(s, row + column * step, encoded, index, s_len)) {
                index++;
                if (index >= s_len) goto end;
            }
            if (row != 0 && row != (numRows - 1)) {
                if (write_encoded(s, (column + 1) * step - row, encoded, index, s_len)) {
                    index++;
                    if (index >= s_len) goto end;
                }
            }
        }
    }
end:
    memcpy(s, encoded, s_len);
    return s;
}