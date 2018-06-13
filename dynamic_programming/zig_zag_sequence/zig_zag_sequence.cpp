//topcoder : zigzag sequence
/*
  A sequence of numbers is called a zig-zag sequence if the differences between successive numbers strictly alternate between positive and negative.
  The first difference (if one exists) may be either positive or negative. A sequence with fewer than two elements is trivially a zig-zag sequence.

  For example, 1,7,4,9,2,5 is a zig-zag sequence because the differences (6,-3,5,-7,3) are alternately positive and negative. 
  In contrast, 1,4,7,2,5 and 1,7,4,5,5 are not zig-zag sequences, the first because its first two differences are positive and 
  the second because its last difference is zero.
  Given a sequence of integers, sequence, return the length of the longest subsequence of sequence that is a zig-zag sequence. 
  A subsequence is obtained by deleting some number of elements (possibly zero) from the original sequence, leaving the remaining elements in their original order.
*/

//topcoder: find longest zizag sequence

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/*

//Greedy approach O(N) time, O(N) space 

bool sameSign(int x, int y) {
  //if (x == 0 || y == 0) return true;
  return ((x >= 0) ^ (y < 0));
}

int longestZigZag(const vector<int>& sequence) {
  //longest zigzag sequence ending in each sequence element
  vector<int> longest{ 1,2 };

  //check base cases
  if (sequence.size() <= 2) return sequence.size();

  //init differences between consecutive pair of sequence elements
  vector<int> diff{ sequence[1] - sequence[0] };

  for (int i = longest.size(); i < sequence.size(); ++i) {
    diff.emplace_back(sequence[i] - sequence[i - 1]);
  }
  int result = 2;

  for (int i = 1, last = 0; i < diff.size(); ++i) {
    if (diff[i] != 0 && !sameSign(diff[i], diff[last])) {
      ++result;
      last = i;
    }
  }
  return result;
}
*/

/* Dynamic Programming: O(N^2) time, O(N) space where N is length of sequence */
int longestZigZag (const vector<int>& sequence) {
  int len = sequence.size();

  if (len == 0) return 0;
  if (len == 1) return 1;
  if (len == 2) return (sequence[0] != sequence[1]) ? 2 : 1;
			
  vector<int> lzs(len,1);
  vector<int> sign(len,-1);
  sign[1] = (sequence[0] < sequence[1]) ? 1 : 0;
			
   int maxZs = 0;
  for (int i = 2; i < len; ++i) {
   
    for (int j = 1; j < i; ++j) {
      int diff = sequence[i] - sequence[j];

      if (diff > 0 && sign[j] == 0) {
	if (lzs[j] + 1 > lzs[i]) {
	  lzs[i] = lzs[j] + 1;
	  sign[i] = 1;//+
	  maxZs = max(maxZs, lzs[i]);
	}
      }
      else if (diff < 0 && sign[j] == 1) {
      if (lzs[j] + 1 > lzs[i]) {
	lzs[i] = lzs[j] + 1;
	sign[i] = 0;//-
	maxZs = max(maxZs, lzs[i]);
      }
    }
  }
  
  }
  return maxZs;
}


int main(void) {
  vector<vector<int>> sequences{{ 1, 7, 4, 9, 2, 5 },{ 1, 17, 5, 10, 13, 15, 10, 5, 16, 8 },{ 44 },
			        { 1, 2, 3, 4, 5, 6, 7, 8, 9 },{ 70, 55, 13, 2, 99, 2, 80, 80, 80, 80, 100, 19, 7, 5, 5, 5, 1000, 32, 32 },
			        { 374, 40, 854, 203, 203, 156, 362, 279, 812, 955, 600, 947, 978, 46, 100, 953, 670, 862, 568, 188, 67,
			        669, 810, 704, 52, 861, 49, 640, 370, 908, 477, 245, 413, 109, 659, 401, 483, 308, 609, 120, 249, 22,
				176, 279, 23, 22, 617, 462, 459, 244 }};

  for (const auto& sequence : sequences) {
    cout << longestZigZag(sequence) << endl;
  }
}
