
#include <iostream>
#include <fstream>
#include <deque>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <cctype>
#include <algorithm>
#include <string>
#include <cassert>

#define BUFFER_SIZE 2048


// Mark all elements as needing traversal using hashmap

// Put excess elements in a series of binary trees, one tree for each customer-product pair

bool isVowel(char c) {
	switch(c) {
	case 'A':
	case 'a':
	case 'E':
	case 'e':
	case 'I':
	case 'i':
	case 'O':
	case 'o':
	case 'U':
	case 'u':
	case 'Y':
	case 'y':
		return true;
	default:
		return false;
	}
}
int getLetterCount(const std::string& str) {
	int count = 0;
	for(auto& c : str) {
		count += (isalpha(c) != 0);
	}
	return count;
}
int getVowelCount(const std::string& str) {
	int count = 0;
	for(auto& c : str) {
		count += isVowel(c);
	}
	return count;
}
int getConsonantCount(const std::string& str) {
	int count = 0;
	for(auto& c : str) {
		count += (isalpha(c) != 0 && !isVowel(c));
	}
	return count;
}
int gcd(int a, int b) {
	int c = a % b;
	while(c != 0) {
		a = b;
		b = c;
		c = a % b;
	}
	return b;
}

float getSuitabilityScore(const std::string& customer, const std::string& product) {
	float score = 0;
	
	if(getLetterCount(product) % 2 == 0) {
		// If the number of letters in the product's name is even then the SS is
		// the number of vowels (a, e, i, o, u, y) in the customer's name multiplied by 1.5. 
		score = getVowelCount(customer)*1.5f;
	} else {
		// If the number of letters in the product's name is odd then the
		// SS is the number of consonants in the customer's name.
		score = getConsonantCount(customer);
	}
	
	// If the number of letters in the product's name shares any common factors
	// (besides 1) with the number of letters in the customer's name then the
	// SS is multiplied by 1.5. 
	if(gcd(getLetterCount(customer),getLetterCount(product)) > 1) {
		score *= 1.5f;
	}
	return score;
}

// Splits a line of data into customers, products, and their suitability scores.
// keys: list of customers or products, whichever is smaller.
// counterparts: list of customers or products, whichever is greater.
// values: mapping of keys to counterparts. Each element in the deque is a map for a single key, mapping to all counterparts.
void parseDiscountData(const std::string& line, std::deque<std::string>& keys, std::deque<std::string>& counterparts, std::deque< std::map<std::string,float> >& values) {
	keys.clear();
	counterparts.clear();
	values.clear();
	
	size_t split = line.find(';');
	size_t current = 0;
	size_t end = line.find(',');
	end = (end==std::string::npos ? split : end);
	
	while(current < split) {
		keys.push_back(line.substr(current,end-current));
		current = end+1;
		end = line.find(',',current);
		end = (end>split ? split : end);
		end = (end==std::string::npos ? split : end);
	}
	current = split+1;
	end = line.find(',',current);
	while(current != std::string::npos+1) {
		counterparts.push_back(line.substr(current,end-current));
		current = end+1;
		end = line.find(',',current);
	}
	
	bool swapped = false;
	if(keys.size() > counterparts.size()) {
		keys.swap(counterparts);
		swapped = true;
	}
	// build suitability score trees
	for(auto& k : keys) {
		values.emplace_back();
		auto& tree = values.back();
		for(auto& c : counterparts) {
			if(!swapped) {
				tree.emplace(c, getSuitabilityScore(k,c));
			} else {
				tree.emplace(c, getSuitabilityScore(c, k));
			}
		}
	}
}

float getBestSalesCombination(const std::deque<std::string>& keys,
							const std::deque<std::string>& counterparts,
							std::deque< std::map<std::string,float> >& values) {
	std::deque< std::pair<std::string,float> > scores;
	std::unordered_map<std::string, int> indexMap;
	std::unordered_set<std::string> marked;

	std::deque< std::map<std::string,float> > debug_values(values);
	
	// Initialize scores
	for(int i=0;i<keys.size();i++) {
		scores.emplace_back(counterparts[i], values[i].at(counterparts[i]));
		values[i].erase(counterparts[i]);
		marked.insert(keys[i]);
		indexMap.emplace(keys[i], i);
	}
	
	// while there are still marked elements:
	while(!marked.empty()) {
		// for every marked element:
		std::string m = *(marked.begin());
		
		int idx_m = indexMap[m];
		
		// unmark element
		marked.erase(marked.begin());
		
		// compare to every other element in the set.
		for(auto k : keys) {
			if(k == m) {
				continue;
			}
			
			// if swapping yields greater value, swap and mark both.
			int idx_k = indexMap[k];
			const std::string& counterpart_k = scores[idx_k].first;
			const std::string& counterpart_m = scores[idx_m].first;
			if(values[idx_m][counterpart_k]+values[idx_k][counterpart_m] > scores[idx_k].second+scores[idx_m].second) {
				marked.insert(m);
				marked.insert(k);
				
				// Put the old values back into the values map
				values[idx_k].insert(scores[idx_k]);
				values[idx_m].insert(scores[idx_m]);

				// Assign the new values to the scores map
				std::swap(scores[idx_k],scores[idx_m]);
				scores[idx_k].second = values[idx_k][scores[idx_k].first];
				scores[idx_m].second = values[idx_m][scores[idx_m].first];
				assert(values[idx_k][scores[idx_k].first] == debug_values[idx_k][scores[idx_k].first]);
				assert(values[idx_m][scores[idx_m].first] == debug_values[idx_m][scores[idx_m].first]);
				values[idx_k].erase(scores[idx_k].first);
				values[idx_m].erase(scores[idx_m].first);
			}
		}
		
		// check against list of "benched" values, swapping if necessary
		// "Benched" values are the currently unused counterparts in the map
		std::map<std::string,float>& bench = values[idx_m];
		std::map<std::string,float>::iterator best = std::max_element(bench.begin(),bench.end());
		if(best->second > scores[idx_m].second) {
			bench.insert(scores[idx_m]);
			scores[idx_m] = *best;
			bench.erase(best);
		}
	}
	// return final amount
	float sum = 0;
	for(auto& s : scores) {
		sum += s.second;
	}
	return sum;
}

int main(int argc, char *argv[]) {
	std::ifstream fid;
	fid.open(argv[1],std::ios::in);
	if(!fid.is_open()) {
		fprintf(stderr, "Error opening input file!");
		return -1;
	}
	
	std::string line;
	std::deque<std::string> keys;
	std::deque<std::string> counterparts;
	std::deque< std::map<std::string,float> > values;
	while(!fid.eof()) {
		getline(fid,line);
		
		parseDiscountData(line, keys, counterparts, values);
		printf("%.2f\n",getBestSalesCombination(keys, counterparts, values));
	}
	
	fid.close();
	return 0;
}