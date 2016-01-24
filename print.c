#include <stdlib.h>
#include <stdio.h>

const char *str = "If\0 life";

int main(int argc, char *argv[]) {
    int nbytes = atoi(argv[1]);
    printf("%.*s\n",nbytes,str);
    return 0;
}
