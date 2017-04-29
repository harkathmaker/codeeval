// https://www.codeeval.com/open_challenges/150/

#include <iostream>
#include <string>
#include <fstream>

int getArabicValue(char c) {
	return c-'0';
}

int getRomanValue(char c) {
	switch(c) {
	case 'I':
		return 1;
	case 'V':
		return 5;
	case 'X':
		return 10;
	case 'L':
		return 50;
	case 'C':
		return 100;
	case 'D':
		return 500;
	case 'M':
		return 1000;
	default:
		return 0;
	}
}

int getAromaticValue(const std::string& line) {
	int i = 0;
	int sum = 0;
	int arabic, roman;
	int lastRoman = -1;
	int lastArabic = 0;
	while(i < line.size()) {
		arabic = getArabicValue(line[i]);
		roman = getRomanValue(line[i+1]);
		sum += arabic*roman;
		// Subtract the last pair
		if(roman > lastRoman) {
			sum -= lastArabic*lastRoman*2;
		}
		lastArabic = arabic;
		lastRoman = roman;
		i += 2;
	}
	return sum;
}

int main_aromatic(int argc, char *argv[]) {
	std::ifstream fid;
	fid.open(argv[1],std::ios::in);
	if(!fid.is_open()) {
		fprintf(stderr, "Error opening input file!");
		return -1;
	}
	
	std::string line;
	while(!fid.eof()) {
		getline(fid, line);
		printf("%d\n", getAromaticValue(line));
	}
	
	fid.close();
	return 0;
}