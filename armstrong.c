// https://www.codeeval.com/open_challenges/82/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BUFFER_SIZE 1024
char buffer[BUFFER_SIZE];

int main(int argc, char *argv[]) {
    FILE *f = fopen(argv[1], "r");
    while (fgets(buffer, BUFFER_SIZE, f)) {

        // Skip empty lines
        if (buffer[0] == '\n') {
            continue;
        }
        size_t length = strlen(buffer)-1;
        int sum = 0;
        for(int i=0;i<length;i++) {
            sum += pow(buffer[i]-'0',length);
        }
        if(sum == atoi(buffer)) {
            printf("True\n");
        } else {
            printf("False\n");
        }
    }
    return 0;
}
