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

int monthlyPayment(int loan, int interest, int term) {
  const int months = 12 * term;
  //const int monthly_interest = (interest * 10) / 12;
  int low = loan / months;
  int high = loan;


  while (low < high) {
    long remaining_loan = loan;
    int m = low + (high - low) / 2;
    for (int i = 0; i < months; ++i) {
      remaining_loan -= m;
      remaining_loan += ceil(static_cast<float>((remaining_loan * interest)) / 12000 );
    }
    if (remaining_loan <= 0) high = m;
    else low = m + 1;
  }
  return low;
}


int main(void) {
  vector<vector<int>> sequences{ { 1000,50,1 },{ 2000000000,6000,1 },{ 1000000,100000,1000 } };

  for (int i = 0; i < sequences.size(); ++i) {
    cout << monthlyPayment(sequences[i][0], sequences[i][1], sequences[i][2]) << endl;
  }
}
