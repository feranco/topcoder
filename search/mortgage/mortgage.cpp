//topcoder mortgage
/*
https://community.topcoder.com/stat?c=problem_statement&pm=2427&rd=4765
When purchasing a new home, the purchasers often take out a loan to pay for it. In this problem, we will be considering loans with the following terms:
At the beginning of each month, the purchasers pay a fixed amount towards settling the loan, which decreases the amount they owe.
At the end of the month, the amount the purchasers owe increases due to interest. Each month, 1/12 of the annual interest rate is added to the amount owed.
Hence, if the annual interest rate is 12%, then the debt increases by 1% each month. 
You may assume that the amount owed after adding interest is always rounded up to the nearest dollar greater than or equal to the actual value.
Your task is, given the annual interest rate in tenths of a percent, the original amount of the loan, and the period over which the loan is to be repaid,
calculate the minimum integral monthly payment so that the loan is repaid in term years or less. All monetary units are in dollars. 

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
