int reverse(int x){
    long long value = x;
    int sign = value < 0;
    
    if (sign) value = -value;
    unsigned char buffer[11];
    int index = 0;
    while (value > 0) {
        printf("i [%d]: %d\n", index, value % 10);
        buffer[index++] = value % 10;
        value = value / 10;
    }
    long long result = 0;
    int digit = 0;
    index--;
    while (index >= 0) {
        printf("x [%d]: %d\n", digit, buffer[index]);
        result += buffer[index--] * pow(10, digit++);
    }
    if (sign) {
        result = -result;
    }
    printf("result: %ld\n", result);
    printf("c1: %d\n", result >= 0 - (long long) 0x80000000);
    printf("c2: %d\n", result < 0x80000000);
    return ((result >= 0 - (long long) 0x80000000) && (result < 0x80000000)) ? result: 0;
}