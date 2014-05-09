// https://www.codeeval.com/open_challenges/38/
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cmath>

void printAlphabetPermutations(std::set<char>& letters, int wordLength) {
    char alphabet[letters.size()];
    std::set<char>::iterator it=letters.begin();
    for(int i=0;i<letters.size();i++) {
        alphabet[i] = *it;
        *it++;
    }
    unsigned int limit = pow(letters.size(),wordLength);
    int k = 0;
    while(k < limit) {
        for(int i=wordLength-1;i>=0;i--) {
            printf("%c",alphabet[(k / int(pow(letters.size(),i))) % letters.size()]);
        }
        k++;
        if(k != limit) {
            printf(",");
        }
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    std::ifstream fid;
    fid.open(argv[1],std::ios::in);
    if(!fid.is_open()) {
        printf("Error opening file.\n");
        return -1;
    }

    std::string line;
    while(!fid.eof()) {
        getline(fid,line);
        if(line == "") {
            continue;
        }

        size_t alphaStart = line.find(',');
        int outputLength = atoi(line.c_str());
        std::set<char> alphabet;
        for(size_t i=alphaStart+1;i<line.size();i++) {
                alphabet.insert(line[i]);
        }
        printAlphabetPermutations(alphabet,outputLength);
    }
    fid.close();
    
    return 0;
}
