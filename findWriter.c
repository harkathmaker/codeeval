// https://www.codeeval.com/open_challenges/97/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
char buffer[BUFFER_SIZE];

int main(int argc, char *argv[]) {
    FILE *f = fopen(argv[1], "r");
    while (fgets(buffer, BUFFER_SIZE, f)) {

        // Skip empty lines
        if (buffer[0] == '\n') {
            continue;
        }

        char *numStart = strchr(buffer, '|');
        numStart = strchr(numStart,' ');
        while(numStart-buffer < strlen(buffer)) {
            printf("%c",buffer[atoi(numStart)-1]);
            numStart = strchr(numStart+1,' ');
        }
        printf("\n");
    }
    return 0;
}
