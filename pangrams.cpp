// https://www.codeeval.com/open_challenges/37/

#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
    std::ifstream fid;
    fid.open(argv[1],std::ios::in);
    if(!fid.is_open()) {
        fprintf(stderr,"Unable to open file.\n");
    }
    std::string line;
    bool charsUsed[26];

    while(!fid.eof()) {
        getline(fid,line);
        if(line.size() == 0) {
            continue;
        }
        for(int i=0;i<26;i++) {
            charsUsed[i] = false;
        }

        for(int i=0;i<line.size();i++) {
            if(line[i] >= 'a' && line[i] <= 'z') {
                charsUsed[line[i]-'a'] = true;
            } else if(line[i] >= 'A' && line[i] <= 'Z') {
                charsUsed[line[i]-'A'] = true;
            }
        }

        bool missingChars = false;
        for(int i=0;i<26;i++) {
            if(!charsUsed[i]) {
                printf("%c",'a'+i);
                missingChars = true;
            }
        }
        if(!missingChars) {
            printf("NULL");
        }
        printf("\n");
    }
    fid.close();
    return 0;
}
