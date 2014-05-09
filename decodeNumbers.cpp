// https://www.codeeval.com/open_challenges/73/

#include <iostream>
#include <fstream>
#include <cstring>

int getDecodePossibilities(const char *msg,int size) {
    if(size == 0) {
        return 1;
    }

    int total = getDecodePossibilities(msg+1,size-1);
    if(size > 1 && ((msg[0] == '1' && msg[1] >= '0' && msg[1] <= '9') ||
                    (msg[0] == '2' && msg[1] >= '0' && msg[1] <= '6'))) {
        // We can decode with either two digits or one
        total += getDecodePossibilities(msg+2,size-2);
    }
    return total;
}

int main(int argc, char *argv[]) {
    std::ifstream fid;
    fid.open(argv[1],std::ios::in);
    if(!fid.is_open()) {
        fprintf(stderr,"Error reading file\n");
    }

    std::string line;
    while(!fid.eof()) {
        getline(fid,line);
        if(line.size() == 0) {
            continue;
        }
        std::cout << getDecodePossibilities(line.c_str(),line.size()) << std::endl;
    }
    fid.close();

    return 0;
}
