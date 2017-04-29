// https://www.codeeval.com/open_challenges/133/

#include <deque>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdlib>

#define BUFFER_SIZE 1024

enum BORDER_STATUS {
        ABOVE_BORDER = 0,
        ON_BORDER        = 1,
        BELOW_BORDER = 2
};

struct Rect {
public:
        int x;
        int y;
        int length;
        int depth;
};

BORDER_STATUS checkPointStatus(int x, int y, int width, int depth) {
        double slope = double(depth)/double(width);
        if(x*depth == y*width) {
                // Exactly on the border
                return ON_BORDER;
        } else if(y > x*slope) {
                return ABOVE_BORDER;
        } else {
                return BELOW_BORDER;
        }
}

bool blockUnderFlight(const Rect& r, int cityWidth, int cityDepth) {
        bool pointAbove = false;
        bool pointBelow = false;
        BORDER_STATUS s = checkPointStatus(r.x,r.y,cityWidth,cityDepth);
        pointAbove = pointAbove || (s == ABOVE_BORDER);
        pointBelow = pointBelow || (s == BELOW_BORDER);

        s = checkPointStatus(r.x,r.y+r.depth,cityWidth,cityDepth);
        pointAbove = pointAbove || (s == ABOVE_BORDER);
        pointBelow = pointBelow || (s == BELOW_BORDER);

        s = checkPointStatus(r.x+r.length,r.y,cityWidth,cityDepth);
        pointAbove = pointAbove || (s == ABOVE_BORDER);
        pointBelow = pointBelow || (s == BELOW_BORDER);

        s = checkPointStatus(r.x+r.length,r.y+r.depth,cityWidth,cityDepth);
        pointAbove = pointAbove || (s == ABOVE_BORDER);
        pointBelow = pointBelow || (s == BELOW_BORDER);

        return (pointBelow && pointAbove);
}

class City {
public:
        City(const char *line) {
                const char *streetEnd = strchr(line,')');
                const char *current = line;
                while(current < streetEnd) {
                        streets.push_back(atoi(current+1));
                        current = strchr(current+1,',');
                }
                current = strchr(line+1,'(');
                while(current != NULL) {
                        avenues.push_back(atoi(current+1));
                        current = strchr(current+1,',');
                }
        }

        int getCityBlocksTraversed() {
                Rect r;
                int traversed = 0;

                for(int i=0;i<streets.size()-1;i++) {
                        for(int j=0;j<avenues.size()-1;j++) {
                                r.x = streets[i];
                                r.y = avenues[j];
                                r.length = streets[i+1]-r.x;
                                r.depth = avenues[j+1]-r.y;
                                traversed += blockUnderFlight(r,streets.back(),avenues.back());
                        }
                }
                return traversed;
        }

private:
        std::deque<int> streets;
        std::deque<int> avenues;
};

int main(int argc, char *argv[]) {
        std::ifstream fid;
        fid.open(argv[1],std::ios::in);
        if(!fid.is_open()) {
                fprintf(stderr,"Error opening file!\n");
                exit(-1);
        }

        char buffer[BUFFER_SIZE];

        while(!fid.eof()) {
                fid.getline(buffer,BUFFER_SIZE);
                if(strlen(buffer) == 0) {
                        continue;
                }
                City c(buffer);
                printf("%d\n",c.getCityBlocksTraversed());
        }

        return 0;
}
