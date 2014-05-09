// https://www.codeeval.com/open_challenges/74/

#include <iostream>
#include <fstream>

int getMinCoins(int price) {
    return price/5 + (price % 5)/3 + (price % 5) % 3;
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
        std::cout << getMinCoins(atoi(line.c_str())) << std::endl;
    }
    fid.close();

    return 0;
}
