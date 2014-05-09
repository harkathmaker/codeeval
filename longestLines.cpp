// https://www.codeeval.com/open_challenges/2/ 

#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <cstdlib>

#define BUFFER_SIZE 128

using namespace std;

typedef deque<string> sdeque;

sdeque longestStrings;
unsigned int lineCount;
unsigned int shortestLineLength;
char buffer[BUFFER_SIZE];

void addLine(const string& str) {
    unsigned int i = 0;
    while(i < longestStrings.size() && longestStrings[i].size() > str.size()) {
        i++;
    }
    longestStrings.insert(longestStrings.begin()+i,str);
    if(longestStrings.size() > lineCount) {
        longestStrings.pop_back();
    }
    if(i == longestStrings.size()-1) {
        shortestLineLength = str.size();
    }
}

void processLine(const string& str) {
    if(str.size() > 0 &&
       (longestStrings.size() < lineCount ||
       str.size() > shortestLineLength)) {
        addLine(str);
    }
}

int main(int argc, char *argv[]) {
    ifstream fid;
    fid.open(argv[1]);

    if(!fid.is_open()) {
        cout << "Error opening file" << endl;
    }

    fid.getline(buffer,BUFFER_SIZE);
    lineCount = atoi(buffer);
    
    while(!fid.eof()) {
        fid.getline(buffer,BUFFER_SIZE);
        processLine(buffer);
    }

    for(int i=0;i<longestStrings.size();i++) {
        cout << longestStrings[i] << endl;
    }

    return 0;
}
