// https://www.codeeval.com/open_challenges/100/

#include <iostream>
#include <fstream>

#define BUFFER_SIZE 64

char buffer[BUFFER_SIZE];

int main(int argc, char *argv[]) {
    std::ifstream fid;
    fid.open(argv[1],std::ios::in);
    if(!fid.is_open()) {
        printf("Error opening file.\n");
        return -1;
    }
    while(!fid.eof()) {
        fid.getline(buffer,BUFFER_SIZE);
        int len = fid.gcount()-1;
        if(len <= 1) {
            continue;
        }
        printf("%d\n",!((buffer[len-1]-'0') % 2));
    }
    return 0;
}
