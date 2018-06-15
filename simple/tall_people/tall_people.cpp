/*

Problem Statement

A group of people stand before you arranged in rows and columns. Looking from above, they form an R by C rectangle of people. 
You will be given a String[] people containing the height of each person. Elements of people correspond to rows in the rectangle. 
Each element contains a space-delimited list of integers representing the heights of the people in that row. Your job is to return 2 specific heights in a int[]. 
The first is computed by finding the shortest person in each row, and then finding the tallest person among them (the "tallest-of-the-shortest"). 
The second is computed by finding the tallest person in each column, and then finding the shortest person among them (the "shortest-of-the-tallest").
*/

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <limits>

using namespace std;

//O(n^2) time: sorting is not necessary since only max/min for each row/col is required
//and a single scan is enough

vector<int> getPeople(vector<string> people) {

  //Convert string heigths to integer
  vector<vector<int>> heights;
  vector<int> result{numeric_limits<int>::min(), numeric_limits<int>::max()};

  for (string row : people) {
    string height;
    istringstream rowStream(row);
    vector<int> rowToInt;
    while (getline(rowStream, height, ' ')) {
      rowToInt.push_back(stoi(height));
    }
    heights.push_back(rowToInt);
  }

  //find tallest of shortest
  int rows = heights.size(), cols = heights[0].size();
  for (int i = 0; i < rows; i++) {
    int shortest = numeric_limits<int>::max();
    for (int j = 0; j < cols; j++) {
      shortest = min(shortest, heights[i][j]);
    }
    result[0] = max(result[0], shortest); 
  }

   for (int i = 0; i < cols; i++) {
    int tallest = numeric_limits<int>::min();
    for (int j = 0; j < rows; j++) {
      tallest = max(tallest, heights[j][i]);
    }
    result[1] = min(result[1], tallest); 
  }

  return result;
  
}

int main(void) {
  vector<vector<string>> sequences{{"9 2 3","4 8 7"}, {"1 2","4 5", "3 6"}, {"1 1","1 1"}};

  for (size_t i = 0; i < sequences.size(); ++i) {
    auto result =  getPeople(sequences[i]);
      cout << result[0] << " " << result[1] << endl;
  }
}
