// https://www.codeeval.com/open_challenges/23/

#include <cstdio>

#define TABLE_SIZE 12

int main(int argc, char *argv[]) {
    for(int i=0;i<TABLE_SIZE;i++) {
        printf("%d",(i+1));
        for(int j=1;j<TABLE_SIZE;j++) {
            printf("%4d",(i+1)*(j+1));
        }
        printf("\n");
    }
    return 0;
}
