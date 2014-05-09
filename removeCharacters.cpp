// https://www.codeeval.com/open_challenges/13/

#include <iostream>
#include <fstream>
#include <string>

#define BUFFER_SIZE 256

std::string removeChars(const std::string& line) {
    size_t lineEnd = line.find(',');
    size_t scrubStart = lineEnd+2;
    char buffer[BUFFER_SIZE];
    int k = 0;
    for(size_t i=0;i<lineEnd;i++) {
        if(line.find(line[i],scrubStart) == std::string::npos) {
            buffer[k] = line[i];
            k++;
        }
    }
    buffer[k] = '\0';
    return std::string(buffer);
}

int main(int argc, char *argv[]) {
    std::ifstream fid;
    std::string line;
    fid.open(argv[1],std::ios::in);
    if(!fid.is_open()) {
        printf("Error opening file.\n");
        return 1;
    }
    while(!fid.eof()) {
        getline(fid,line);
        if(line.size() == 0) {
            continue;
        }
        std::string scrubbed = removeChars(line);
        printf("%s\n",scrubbed.c_str());
    }
    return 0;
}
