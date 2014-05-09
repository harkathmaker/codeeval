// https://www.codeeval.com/open_challenges/14/

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

bool generateNextPermutation(std::string& str) {
    int k,l;
    k = str.size()-2;
    while(k > -1 && str[k] >= str[k+1]) {
        k--;
    }
    if(k == -1) {
        return false;
    }
    l = str.size()-1;
    while(str[k] >= str[l]) {
        l--;
    }
    std::swap(str[k],str[l]);
    std::reverse(str.begin()+k+1,str.end());
    return true;
}

int main(int argc, char *argv[]) {
    std::ifstream fid;
    std::string str;
    fid.open(argv[1],std::ios::in);
    if(!fid.is_open()) {
        printf("Error opening file.\n");
    }

    while(!fid.eof()) {
        getline(fid,str);
        if(str.size() == 0) {
            continue;
        }
        std::sort(str.begin(),str.end());
        while(1) {
            printf("%s",str.c_str());
            if(generateNextPermutation(str)) {
                printf(",");
            } else {
                break;
            }
        }
        printf("\n");
    }
    return 0;
}
