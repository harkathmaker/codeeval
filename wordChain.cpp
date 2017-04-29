// https://www.codeeval.com/open_challenges/135/

#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <deque>
#include <string>
#include <algorithm>

class Word {
public:
	Word(char start, char end): _start(start), _end(end) {
	}
	bool linkWords(const Word& other) {
		if(other._start == _end) {
			linkedWords.insert(&other);
			return true;
		} else {
			return false;
		}
	}
	const std::set<const Word*>& getLinkedWords() const {
		return linkedWords;
	}
private:
	char _start;
	char _end;
	std::set<const Word*> linkedWords;
};

int _getLongestChain(const std::deque<Word>& graph,std::map<const Word*,bool>& used,const Word* w,int length) {
	used[w] = true;
	const std::set<const Word*>& links = w->getLinkedWords();
	int newLength = length;
	for(std::set<const Word*>::iterator it=links.begin();it!=links.end();it++) {
		if(!used[*it]) {
			newLength = std::max(newLength,_getLongestChain(graph,used,*it,length+1));
		}
	}
	used[w] = false;
	return newLength;
}

int getLongestChain(const std::deque<Word>& graph) {
	std::map<const Word*,bool> used;
	for(int i=0;i<graph.size();i++) {
		used.insert(std::pair<const Word*,bool>(&graph[i],false));
	}
	int longest = 0;
	for(int i=0;i<graph.size();i++) {
		longest = std::max(longest,_getLongestChain(graph,used,&graph[i],1));
	}
	return longest;
}

int main(int argc, char *argv[]) {
	std::ifstream fid;
	fid.open(argv[1],std::ios::in);
	if(!fid.is_open()) {
		fprintf(stderr,"Error opening file!\n");
		exit(-1);
	}

	std::deque<Word> graph;
	std::string line;
	while(!fid.eof()) {
		getline(fid,line);
		if(line.size() == 0) {
			continue;
		}
		size_t wordStart = 0;
		size_t wordEnd = line.find(',');
		graph.clear();
		while(wordEnd != std::string::npos) {
			graph.push_back(Word(line[wordStart],line[wordEnd-1]));
			wordStart = wordEnd+1;
			wordEnd = line.find(',',wordStart);
		}
		graph.push_back(Word(line[wordStart],line[line.size()-1]));

		for(int i=0;i<graph.size();i++) {
			for(int j=0;j<graph.size();j++) {
				if(i == j) continue;
				graph[i].linkWords(graph[j]);
			}
		}

		int chainLength = getLongestChain(graph);
		if(chainLength > 1) {
			printf("%d\n",chainLength);
		} else {
			printf("None\n");
		}
	}

	return 0;
}