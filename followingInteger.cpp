// https://www.codeeval.com/open_challenges/44/

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
        if(!generateNextPermutation(str)) {
            std::reverse(str.begin(),str.end());
            // Start of nonzero digits
            std::string::iterator it = str.begin();
            while(*it == '0') {
                it++;
            }
            std::swap(*it,str[0]);
            str.insert(str.begin()+1,'0');
        }
        printf("%s\n",str.c_str());
    }
    return 0;
}
