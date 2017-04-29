// https://www.codeeval.com/open_challenges/49/

#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <deque>
#include <algorithm>

#define MIN_CLUSTER_SIZE 3

typedef std::set<std::string> EmailSet;
typedef std::pair<std::string,EmailSet> SetPair;
typedef std::map<std::string,EmailSet> ConnectionMap;

std::pair<std::string,std::string> getEmailsFromLine(const std::string& line) {
	size_t em1 = line.find('\t');
	size_t em2 = line.find('\t',em1+1);
	
	return std::pair<std::string,std::string>(line.substr(em1+1,em2-em1-1),line.substr(em2+1));
}

void printCluster(const std::deque<std::string> cluster) {
	if(cluster.size() >= MIN_CLUSTER_SIZE) {
		for(int i=0;i<cluster.size()-1;i++) {
			printf("%s, ",cluster[i].c_str());
		}
		printf("%s\n",cluster.back().c_str());
	}
}

int _main_(int argc, char *argv[]) {
	std::ifstream fid;
	fid.open(argv[1],std::ios::in);
	
	if(!fid.is_open()) {
		fprintf(stderr,"Error opening file!\n");
		exit(-1);
	}
	// If memory is still an issue, do a pre-pass on input.
	//   Compile map of all inputs on the left side. If they never send, they can't be part of a cluster.
	//   Traverse input map and assign numeric keys to each address. Use for processing the rest of the data.
	//   Create array that inversely maps numbers to addresses for output.

	ConnectionMap connectionList;
	// Traverse input
	// When finding a new string, add a set to the map of sets
	std::string line;
	while(!fid.eof()) {
		getline(fid,line);
		std::pair<std::string,std::string> addresses = getEmailsFromLine(line);
		
		// Creates new set if none exists
		EmailSet& es = connectionList[addresses.first];
		// Add link to the appropriate set for every pair
		es.insert(addresses.second);
	}

	// Do second pass through connectionList, removing any links that are unidirectional
	//printf("Looping through all sets\n");
	for(ConnectionMap::iterator it=connectionList.begin();it!=connectionList.end();it++) {
		EmailSet& es = it->second;
		//printf("Scanning %s\n",(it->first).c_str());
		for(EmailSet::iterator es_it=es.begin();es_it!=es.end(); ){
			if(connectionList.count(*es_it) == 0 || connectionList[*es_it].count(it->first) == 0) {
				// Found a unidirectional connection
				//printf("%s's connection to %s was unidirectional; removing.\n",(it->first).c_str(),(*es_it).c_str());
				es.erase(es_it++);
			} else {
				++es_it;
			}
		}
	}

	// (map will be sorted in ascending? order)
	/*printf("Remaining connections:\n");
	for(ConnectionMap::iterator it=connectionList.begin();it!=connectionList.end();it++) {
		EmailSet& es = it->second;
		printf("%s:\n",(it->first).c_str());
		for(EmailSet::iterator es_it=es.begin();es_it!=es.end();es_it++) {
			printf("\t%s\n",(*es_it).c_str());
		}
	}*/

	// for every entry in setmap:
	for(ConnectionMap::iterator cm_it=connectionList.begin();cm_it!=connectionList.end();cm_it++) {
		std::deque<std::string> cluster;
		std::deque<std::string> rejects;

		//   loop through entries in the set. Start an array of addresses corresponding to a cluster. Append any that do not match this cluster to a second array.
		cluster.push_back(cm_it->first);
		EmailSet& es = cm_it->second;
		bool repeatedCluster = false;
		for(EmailSet::iterator es_it=es.begin();es_it!=es.end();es_it++) {
			//if(*es_it < cm_it->first) {
			//	continue;
			//}
			bool inCluster = true;
			for(int i=1;i<cluster.size();i++) {
				if(connectionList[*es_it].count(cluster[i]) == 0) {
					inCluster = false;
					break;
				}
			}
			if(inCluster) {
				cluster.push_back(*es_it);
				repeatedCluster |= (*es_it < cm_it->first);
			} else {
				rejects.push_back(*es_it);
			}
		}

		//   print out first array (this is the first cluster alphabetically).
		if(!repeatedCluster) {
			printCluster(cluster);
		}
		cluster.clear();

		while(!rejects.empty()) {
			//   for every entry in the rejects array:
			//     loop through A's connections again, constructing a new cluster array.
			cluster.push_back(cm_it->first);
			cluster.push_back(rejects.front());
			rejects.pop_front();
			EmailSet& es = cm_it->second;
			bool repeatedCluster = false;
			for(EmailSet::iterator es_it=es.begin();es_it!=es.end();es_it++) {
				bool inCluster = true;
				if(*es_it == cluster[1]) {
					// Don't add the reject starting the new cluster twice
					continue;
				}
				for(int i=1;i<cluster.size();i++) {
					if(connectionList[*es_it].count(cluster[i]) == 0) {
						inCluster = false;
						break;
					}
				}
				if(inCluster) {
					// Remove any addresses found in this way from the rejects array.
					std::deque<std::string>::iterator it=std::find(rejects.begin(),rejects.end(),*es_it);
					if(it != rejects.end()) {
						rejects.erase(it);
					}
					cluster.push_back(*es_it);
					// TODO: stop building the cluster if it is found to be repeated. Confirm this is correct.
					repeatedCluster |= (*es_it < cm_it->first);
				}
			}

			//     print out cluster array, if more than minimum number of elements.
			//   repeat above until all rejects have been removed.
			if(!repeatedCluster) {
				std::sort(cluster.begin(),cluster.end());
				printCluster(cluster);
			}
			cluster.clear();
		}
	}
	
	

	return 0;
}