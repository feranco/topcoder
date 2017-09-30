//topcoder: badneighbors
/*
The old song declares "Go ahead and hate your neighbor", and the residents of Onetinville have taken those words to heart. 
Every resident hates his next-door neighbors on both sides. Nobody is willing to live farther away from the town's well than his neighbors, 
so the town has been arranged in a big circle around the well. Unfortunately, the town's well is in disrepair and needs to be restored. 
You have been hired to collect donations for the Save Our Well fund.

Each of the town's residents is willing to donate a certain amount, as specified in the int[] donations, which is listed in clockwise order around the well. 
However, nobody is willing to contribute to a fund to which his neighbor has also contributed. 
Next-door neighbors are always listed consecutively in donations, except that the first and last entries in donations are also for next-door neighbors. 
You must calculate and return the maximum amount of donations that can be collected.
*/

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
#if 0
//first solution: backtracking
//for each donation k there are two possibilities:
//the donation is in the fund, so the next donation in the fund can be k+2
//the donation is not in the fund, so the next donation in the fund can be k+1
//the max donation is the max among them
int maxDonations (const vector<int>& donation, int k, bool first_donate) {
  if (k >= donation.size()) return 0;
  //discard last donation if first donation is true
  int k_donation = (first_donate = true && k ==  donation.size()-1) ? 0 : donation[k];
  return max (k_donation + maxDonations(donation, k+2,first_donate), maxDonations(donation, k+1,first_donate));
}

int maxDonations (const vector<int>& donation) {
  return max(donation[0] + maxDonations(donation, 2,true), maxDonations(donation, 1,false));  
}
#endif

//second solution: dp top down
//the max donation is the max among them
int maxDonations (const vector<int>& donation, int k, bool first_donate, vector<vector<int>>* table_ptr) {
  if (k >= donation.size()) return 0;
  vector<vector<int>>& table = *table_ptr;
  if (table[first_donate ? 1 : 0][k] > 0) return table[first_donate ? 1 : 0][k];
  //discard last donation if first donation is true
  int k_donation = (first_donate = true && k ==  donation.size()-1) ? 0 : donation[k];
  table[first_donate ? 1 : 0][k] = max (k_donation + maxDonations(donation, k+2,first_donate, table_ptr), maxDonations(donation, k+1,first_donate, table_ptr));
  return table[first_donate ? 1 : 0][k];
}

int maxDonations (const vector<int>& donation) {
  vector<vector<int>> table(2,vector<int>(donation.size(),-1));
  return max(donation[0] + maxDonations(donation, 2,true, &table), maxDonations(donation, 1,false, &table));  
}

int main (void) {
  vector<vector<int>> donations{{ 10, 3, 2, 5, 7, 8 }, { 11, 15 }, { 7, 7, 7, 7, 7, 7, 7 },
			        { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5 }, { 94, 40, 49, 65, 21, 21, 106, 80, 92, 81, 679, 4, 61,  
				  6, 237, 12, 72, 74, 29, 95, 265, 35, 47, 1, 61, 397, 52, 72, 37, 51, 1, 81, 45, 435, 7, 36, 57, 86, 81, 72 }};				     
  cout << maxDonations(donations[4]);

}
