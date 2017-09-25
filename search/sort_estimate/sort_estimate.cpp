//topcoder: SortEstimate
//https://community.topcoder.com/stat?c=problem_statement&pm=3561&rd=6519
/*
  You have implemented a sorting algorithm that requires exactly c*n*lg(n) nanoseconds to sort n integers.
  Here lg denotes the base-2 logarithm. Given time nanoseconds, return the largest double n such that c*n*lg(n) <= time.
*/

#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

const double limit = 1e-9;

double howMany(int c, int time) {
	double low = 1, high = 1 << 30;

	while (fabs(high-low)/high > limit) {
		double m = low + (high - low) / 2;
		if (c*m*(log2(m)) <= time) low = m;
		else high = m;
	}
	//cout << high << " " << low << " " << (high - low) << endl;
	return low;
}

int main(void) {
	vector<pair<int, int>> inputs{ { 1,8 },{ 2,16 },{ 37,12392342 },{ 1,2000000000 } };

	//cout << limit;
	for (const auto& input : inputs) cout << howMany(input.first, input.second) << endl;
	cout << log2(4);

}
