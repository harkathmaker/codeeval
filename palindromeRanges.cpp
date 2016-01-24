// https://www.codeeval.com/open_challenges/47/

#include <iostream>
#include <fstream>

// Implementation from http://stackoverflow.com/questions/199184/how-do-i-check-if-a-number-is-a-palindrome
bool isPalindrome(int num) {
    int n = num;
    int rev = 0;
    while(num > 0) {
        int dig = num % 10;
        rev = rev * 10 + dig;
        num = num / 10;
    }
    return n == rev;
}
int getInterestingSubsetCount(int start, int end) {
    int count = 0;
    int range = end-start+1;
    bool palindromes[range];
    for(int i=0;i<range;i++) {
        palindromes[i] = isPalindrome(start+i);
    }
    for(int i=0;i<range;i++) {
        int sum = 0;
        for(int k=i;k<range;k++) {
            sum += palindromes[k];
            // Increment count if the sum so far is even
            count += (sum+1) % 2;
        }
    }
    return count;
}
int main(int argc, char *argv[]) {
    std::ifstream fid;
    fid.open(argv[1],std::ios::in);
    if(!fid.is_open()) {
        fprintf(stderr,"Error opening file!\n");
        return -1;
    }
    while(!fid.eof()) {
        std::string n1_str,n2_str;
        getline(fid,n1_str,' ');
        getline(fid,n2_str);
        if(n1_str.size() == 0) {
            continue;
        }
        int n1 = atoi(n1_str.c_str());
        int n2 = atoi(n2_str.c_str());

        printf("%d\n",getInterestingSubsetCount(n1,n2));
    }
    fid.close();
}
