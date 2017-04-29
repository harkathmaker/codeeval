// https://www.codeeval.com/open_challenges/153/

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

#define BUFFER_SIZE 128

int getOpenLocks(int n, int m) {
	if(m == 1) {
		return n-1;
	}
	int openLocks = n/2 + n % 2;
	// Even multiples of 3 are always unlocked
	openLocks += n/6;
	// Odd multiples of 3 are locked or unlocked depending on m
	openLocks -= (n+3)/6 * ((m-1) % 2 == 1);
	if(n % 2 == 0) {
		if(n % 3 == 0) {
			openLocks--;
		} else {
			openLocks++;
		}
	} else {
		if(n % 3 == 0) {
			openLocks += ((m-1) % 2 == 1 ? 1 : -1);
		} else {
			openLocks--;
		}
	}
	return openLocks;
}

int main_locks(int argc, char *argv[]) {
	std::ifstream fid;
	fid.open(argv[1],std::ios::in);
	if(!fid.is_open()) {
		fprintf(stderr, "Error opening input file!");
		return -1;
	}
	
	char line[BUFFER_SIZE];
	while(!fid.eof()) {
		fid.getline(line,BUFFER_SIZE);
		
		int locks = atoi(line);
		int passes = atoi(strchr(line,' '));
		printf("%d\n", getOpenLocks(locks,passes));
	}
	
	fid.close();
	return 0;
}