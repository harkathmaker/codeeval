// https://www.codeeval.com/open_challenges/116/

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>

#define BUFFER_SIZE 2048

char buffer[BUFFER_SIZE];

std::map<int,char> morseMap;

// Interprets morse codes as base-3 numbers that map to characters.
int morseValue(const std::string& code) {
    int value = 0;
    for(size_t i=0;i<code.size();i++) {
        value *= 3;
        if(code[i] == '.') {
            value += 1;
        } else if(code[i] == '-') {
            value += 2;
        }
    }
    return value;
}

#define ADD_MORSE_ENTRY(s,c) morseMap.insert(std::pair<int,char>(morseValue(s),c))

void defineMorseValues() {
    ADD_MORSE_ENTRY(".-",'A');
    ADD_MORSE_ENTRY("-...",'B');
    ADD_MORSE_ENTRY("-.-.",'C');
    ADD_MORSE_ENTRY("-..",'D');
    ADD_MORSE_ENTRY(".",'E');
    ADD_MORSE_ENTRY("..-.",'F');
    ADD_MORSE_ENTRY("--.",'G');
    ADD_MORSE_ENTRY("....",'H');
    ADD_MORSE_ENTRY("..",'I');
    ADD_MORSE_ENTRY(".---",'J');
    ADD_MORSE_ENTRY("-.-",'K');
    ADD_MORSE_ENTRY(".-..",'L');
    ADD_MORSE_ENTRY("--",'M');
    ADD_MORSE_ENTRY("-.",'N');
    ADD_MORSE_ENTRY("---",'O');
    ADD_MORSE_ENTRY(".--.",'P');
    ADD_MORSE_ENTRY("--.-",'Q');
    ADD_MORSE_ENTRY(".-.",'R');
    ADD_MORSE_ENTRY("...",'S');
    ADD_MORSE_ENTRY("-",'T');
    ADD_MORSE_ENTRY("..-",'U');
    ADD_MORSE_ENTRY("...-",'V');
    ADD_MORSE_ENTRY(".--",'W');
    ADD_MORSE_ENTRY("-..-",'X');
    ADD_MORSE_ENTRY("-.--",'Y');
    ADD_MORSE_ENTRY("--..",'Z');
    ADD_MORSE_ENTRY(".----",'1');
    ADD_MORSE_ENTRY("..---",'2');
    ADD_MORSE_ENTRY("...--",'3');
    ADD_MORSE_ENTRY("....-",'4');
    ADD_MORSE_ENTRY(".....",'5');
    ADD_MORSE_ENTRY("-....",'6');
    ADD_MORSE_ENTRY("--...",'7');
    ADD_MORSE_ENTRY("---..",'8');
    ADD_MORSE_ENTRY("----.",'9');
    ADD_MORSE_ENTRY("-----",'0');
    ADD_MORSE_ENTRY("",' ');
}

int main(int argc, char *argv[]) {
    defineMorseValues();
    std::ifstream fid;
    // Maximum length of morse string is 5 (add one for null terminator)
    char code[6];

    fid.open(argv[1],std::ios::in);
    if(!fid.is_open()) {
        printf("Error opening file.\n");
    }

    fid.getline(buffer,BUFFER_SIZE);
    while(!fid.eof()) {
        if(fid.fail()) {
            printf("Line exceeded buffer size.\n");
        }

        size_t start = 0;
        size_t i;
        while(start < (unsigned int)fid.gcount()) {
            i = 0;
            while(buffer[start+i] != ' ' && buffer[start+i] != '\0') {
                i++;
            }
            strncpy(code,buffer+start,i);
            code[i] = '\0';
            printf("%c",morseMap[morseValue(code)]);
            start += i+1;
        }

        printf("\n");
        fid.getline(buffer,BUFFER_SIZE);
    }
    return 0;
}
