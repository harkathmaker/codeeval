// https://www.codeeval.com/open_challenges/98/

#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>

bool pointInCircle(float cx, float cy, float radius, float px, float py) {
	float dist = sqrt(pow(cx-px,2)+pow(cy-py,2));
	return dist <= radius;
}

void parseLine(const std::string& line) {
	float cx,cy,radius,px,py;
	const char *l = line.c_str();
	const char *p = strchr(l,'(')+1;
	cx = atof(p);
	p = strchr(p,' ')+1;
	cy = atof(p);
	p = strchr(p,':')+1;
	radius = atof(p);
	p = strchr(p,'(')+1;
	px = atof(p);
	p = strchr(p,',')+1;
	py = atof(p);

	if(pointInCircle(cx,cy,radius,px,py)) {
		printf("true\n");
	} else {
		printf("false\n");
	}
}

int main(int argc, char *argv[]) {
	std::ifstream fid;
	fid.open(argv[1],std::ios::in);
	if(!fid.is_open()) {
		fprintf(stderr,"Error opening file!\n");
		return -1;
	}

	std::string line;
	while(!fid.eof()) {
		getline(fid,line);
        if(line.size() == 0) {
            continue;
        }
		parseLine(line);
	}

	fid.close();

	return 0;
}
