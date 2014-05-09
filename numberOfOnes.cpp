#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
    std::ifstream fid;
    fid.open(argv[1]);
    if(!fid.is_open()) {
        printf("Error opening file\n");
        return 1;
    }
    std::string line;
    int ones;
    while(!fid.eof()) {
        getline(fid,line);
        if(line.size() == 0) {
            continue;
        }
        ones = 0;
        int n = atoi(line.c_str());
        while(n > 0) {
            ones += (n % 2);
            n >>= 1;
        }
        printf("%d\n",ones);
    }
    return 0;
}
