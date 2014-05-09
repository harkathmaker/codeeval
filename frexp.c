#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EXPONENT_BIAS 1023
#define MANTISSA_LENGTH 52
#define EXPONENT_LENGTH 11

union exDouble_t {
    double doubleValue;
    unsigned long long asLong;
    char   asChars[sizeof(double)];
} exDouble;

union exFloat_t {
    float floatValue;
    unsigned int intValue;
};

void printBinary(char *n) {
    int i,j;
    for(i=sizeof(double)-1;i>=0;i--) {
        for(j=7;j>=0;j--) {
            printf("%d",(n[i] & 1<<j) != 0);
        }
    }
    printf("\n");
}

float convertToFloat(unsigned long long n) {
    int i;
    float result = 1.f;
    for(i=8*sizeof(unsigned long long)-1;i>=0;i--) {
        if(n & 1<<i) {
            // pow only works properly with positive numbers
            result += 1.f / powf(2,-(i-8*sizeof(unsigned long long)));
        }
    }
    return result;
}

void frexp_double(union exDouble_t d) {
    unsigned long long sign = (d.asLong>>63 & 1) != 0;
    unsigned long long mantissaMask = 0x000fffffffffffff;
    unsigned long long exponentMask = 0x7ff0000000000000;
    unsigned long long mantissa = (d.asLong & mantissaMask);
    printf("Original number: %f\n",d.doubleValue);
    printf("Sign: %llu\nExponent: %llu\nMantissa: %f\n",
           sign,
           -EXPONENT_BIAS + ((d.asLong & exponentMask) >> MANTISSA_LENGTH),
           convertToFloat(mantissa)
           );
    printBinary(d.asChars);
}

//void frexp_int(exDouble d) {
//}
//
//void frexp_chars(exDouble d) {
//}

int main(int argc, char *argv[]) {
    printf("sizeof(unsigned long long) = %lu\n",sizeof(unsigned long long));
    exDouble.doubleValue = 1.0;
    frexp_double(exDouble);
    exDouble.doubleValue = 2.0;
    frexp_double(exDouble);
    exDouble.doubleValue = 1.5;
    frexp_double(exDouble);
    exDouble.doubleValue = -2.0;
    frexp_double(exDouble);
    return 0;
}
