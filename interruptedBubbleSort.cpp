// https://www.codeeval.com/open_challenges/158/

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <deque>
#include <utility>

#define BUFFER_SIZE 2048

void printList(const std::deque<int>& list) {
	for(auto it=list.begin();it != list.end();it++) {
		printf("%d ",*it);
	}
	printf("\n");
}

void interruptedSort(std::deque<int>& list, int iterations) {
	for(int k=0;k<iterations;k++) {
		for(int i=0;i<list.size()-1;i++) {
			if(list[i] > list[i+1]) {
				std::swap(list[i],list[i+1]);
			}
		}
	}
}

int bubble_main(int argc, char *argv[]) {
	std::ifstream fid;
	fid.open(argv[1],std::ios::in);
	if(!fid.is_open()) {
		fprintf(stderr, "Error opening input file!");
		return -1;
	}
	
	char line[BUFFER_SIZE];
	std::deque<int> list;
	while(!fid.eof()) {
		fid.getline(line,BUFFER_SIZE);
		
		const char *iterDelim = strchr(line,'|');
		char *pos = line;
		while(pos < iterDelim && pos[1] != '|') {
			list.push_back(atoi(pos));
			pos = strchr(pos+1,' ');
		}
		int iters = atoi(iterDelim+1);
		interruptedSort(list,iters);
		printList(list);
		list.clear();
	}
	
	fid.close();
	return 0;
}