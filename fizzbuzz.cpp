// http://www.codeeval.com/open_challenges/1/

#include <iostream>
#include <fstream>

void fizzbuzz(int a, int b, int n) {
    for(int i=1;i<=n;i++) {
        bool special = false;
        if(i % a == 0) {
            special = true;
            std::cout << "F";
        }
        if(i % b == 0) {
            special = true;
            std::cout << "B";
        }
        if(!special) {
            std::cout << i;
        }
        if(i < n) {
            std::cout << " ";
        }
    }
}

int main(int argc, char *argv[]) {
    std::ifstream fid;
    fid.open(argv[1]);
    int a,b,n;
    
    while(!fid.eof()) {
        fid >> a;
        fid >> b;
        fid >> n;
        fizzbuzz(a,b,n);
        std::cout << std::endl;
    }

    return 0;
}
