//topcoder: avoid roads
//https://community.topcoder.com/stat?c=problem_statement&pm=1889&rd=4709
/*
  In the city, roads are arranged in a grid pattern. Each point on the grid represents a corner where two blocks meet.
  The points are connected by line segments which represent the various street blocks. Using the cartesian coordinate system, we can assign a pair of integers to each corner as shown below.
  You are standing at the corner with coordinates 0,0. Your destination is at corner width,height. You will return the number of distinct paths that lead to your destination.
  Each path must use exactly width+height blocks. In addition, the city has declared certain street blocks untraversable. These blocks may not be a part of any path.
  You will be given a String[] bad describing which blocks are bad. If (quotes for clarity) "a b c d" is an element of bad, it means the block from corner a,b to corner c,d is untraversable.
  For example, let's say
  width  = 6
  length = 6
  bad = {"0 0 0 1","6 6 5 6"}
  The picture below shows the grid, with untraversable blocks darkened in black. A sample path has been highlighted in red.
 
  Class:	AvoidRoads
  Method:	numWays
  Parameters:	int, int, String[]
  Returns:	long
  Method signature:	long numWays(int width, int height, String[] bad)
  (be sure your method is public)
*/
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std;

class AvoidRoads {
  struct Blocked {
    int start_x, start_y, end_x, end_y;
    Blocked (int start_x, int start_y, int end_x, int end_y):
      start_x(start_x),start_y(start_y),end_x(end_x),end_y(end_x){}
    bool operator==(const Blocked& rhs) const{
      return (start_x == rhs.start_x && start_y == rhs.start_y &&
	      end_x == rhs.end_x && end_y == rhs.end_y);
    }
  };
    
  struct BlockedHash {
    size_t operator() (const Blocked& block) const {
      return hash<int>()(block.start_x) ^ hash<int>()(block.start_y) ^
	hash<int>()(block.end_x) ^ hash<int>()(block.end_y);
    }
  };
    
  //height = n_row, width = n_cols
  unordered_set<Blocked,BlockedHash> parseInput (int width, int height, vector<string> bad) {
    unordered_set<Blocked,BlockedHash> bad_roads;
    for (const string& roads : bad) {
      stringstream ss(roads);
      int x, y, z, w;
      while (ss >> x >> y >> z >> w) bad_roads.emplace(Blocked{x,y,z,w});
    }
    return bad_roads;
  }
    
public:
  long numWays (int width, int height, vector<string> bad) {
    auto bad_roads = parseInput( width, height, bad);
    vector<vector<int>> num_ways(height+1, vector<int>(width+1, 0));
    num_ways[0][0] = 1;
    for (int i = 1; i <= width; ++i) {
      if ((bad_roads.find({i-1, 0, i, 0})) == bad_roads.end()) num_ways[i][0] = 1;
      else break;
    }
    for (int i = 1; i <= height; ++i){
      if ((bad_roads.find({0, i-1, 0, i})) == bad_roads.end()) num_ways[0][i] = 1;
      else break;
    }
    for (int i = 1; i <= width; ++i) {
      for (int j = 1; j <=height; ++j) {
	int from_left = ((j>0) && (bad_roads.find({i, j-1, i, j})) == bad_roads.end()) ? num_ways[i][j-1] : 0;
	int from_down = ((i>0) && (bad_roads.find({i-1, j, i, j})) == bad_roads.end()) ? num_ways[i-1][j] : 0;
	num_ways[i][j] = from_left + from_down;
      }
    }
    return num_ways[height][width];
  }
};

int main (void) {
  vector<int> width{6,1,2};
  vector<int> height{6,1,2};
  vector<vector<string>> bad{{"0 0 0 1","5 6 6 6"},{},{"0 0 1 0", "1 2 2 2", "1 1 2 1"}};
  for (int i = 0; i < width.size(); ++i) {
    AvoidRoads ar;
    cout << ar.numWays(width[i], height[i], bad[i]) << endl;   
  }
}
