// https://www.codeeval.com/open_challenges/122/

#include <iostream>
#include <fstream>

#define BUFFER_SIZE 2048


int main(int argc, char *argv[]) {
    std::ifstream fid;
    fid.open(argv[1],std::ifstream::in);
    char buffer[BUFFER_SIZE];

    if(!fid.is_open()) {
        printf("Unable to open file.\n");
        return -1;
    }

    fid.getline(buffer,BUFFER_SIZE);
    while(!fid.eof()) {
        if(fid.fail()) {
            printf("Line length exceeded buffer size.\n");
            return -2;
        }
        bool wroteDigit = false;
        for(int i=0;i<fid.gcount();i++) {
            if(buffer[i] >= '0' && buffer[i] <= '9') {
                printf("%c",buffer[i]);
                wroteDigit = true;
            } else if(buffer[i] >= 'a' && buffer[i] <= 'j') {
                printf("%c",'0' + (buffer[i]-'a'));
                wroteDigit = true;
            }
        }
        if(!wroteDigit) {
            printf("NONE");
        }
        printf("\n");
        fid.getline(buffer,BUFFER_SIZE);
    }

    return 0;
}
