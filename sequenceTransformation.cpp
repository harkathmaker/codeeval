// https://www.codeeval.com/open_challenges/130/

#include <iostream>
#include <fstream>

bool transformationPossible(const char binary[],const char letters[]) {
    if(binary[0] == '\0' && letters[0] == '\0') {
        return true;
    } else if(binary[0] == '\0' || letters[0] == '\0') {
        return false;
    } else if(binary[0] == '0' && letters[0] == 'B') {
        // Dead end; we can't turn 0 into B
        return false;
    } else {
        int k = 0;
        while(letters[k] == letters[0]) {
            k++;
        }
        while(k > 0) {
            if(transformationPossible(&binary[1],&letters[k])) {
                return true;
            }
            k--;
        }
        return false;
    }
}

int main(int argc, char *argv[]) {
    std::ifstream fid;

    fid.open(argv[1],std::ios::in);
    if(!fid.is_open()) {
        printf("Error opening file.\n");
    }

    std::string line;
    std::string binary;
    std::string letters;
    while(!fid.eof()) {
        getline(fid,line);
        if(line.size() == 0) {
            continue;
        }
        size_t space = line.find(' ');
        binary = line.substr(0,space);
        letters = line.substr(space+1);
        if(transformationPossible(binary.c_str(),letters.c_str())) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}
