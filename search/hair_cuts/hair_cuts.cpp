//topcoder: haircuts
/*
  Our barbershop opens at 9:00 am and closes at 5:00 pm, but (of course) the barber keeps working until all the customers who entered the shop before 5:00 have been served. 
  Each customer enters the shop and if the barber is free, immediately starts getting his hair cut. 
  Otherwise, the customer waits until everyone who entered before him has finished getting their hair cut.
  We have the sequence of times when customers entered the shop and we know when the last customer left the shop. We also know that each haircut took at least 5 minutes. 
  We want to get a bound on how long the longest haircut took.
  Create a class HairCuts that contains a method maxCut that is given String[] enter and String lastExit and that returns the smallest possible time (in minutes) that the longest haircut took. 
  If the inputs are inconsistent with the rule that each haircut takes at least 5 minutes, return -1.
  The enter times and the lastExit are 5 character Strings in the format hh:mm with hh being a 12 hour time.
*/

#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Haircuts {
  //convert time to int (09:00 corresponds to 0)
  int parseTime (const string& time) {
    stringstream ss(time);
    string t;
    getline(ss, t, ':');
    int result = stoi(t);
    result = (result < 9) ? result + 12 : result;
    result = (result-9) * 60;
    getline(ss, t, ':');
    result+=stoi(t);
    return result;
  }

  //return true i the input upper bound m allows to complete
  //haircuts within the last exit time, false otherwise
  bool haircutsCompleted (double m) {
    double temp = 0;
    for (int i = 0, size = enter_time.size(); i < size; ++i)
      {
	if (enter_time[i] > temp)
	  temp = enter_time[i];
	temp += m;
      }
    return static_cast<int>(temp) >= last_exit_time;
  }

  //check if a valid solution exists
  bool isValidInput(void) {
    vector<pair<int,int>> time_limits;
    for (int i = 0; i <= enter_time.size()-1; ++i) {
      time_limits.emplace_back(make_pair(enter_time[i]+5, last_exit_time-((enter_time.size()-1-i)*5)));
    }
    time_limits.emplace_back(make_pair(enter_time.back()+5, last_exit_time-5));

    for (const auto& limit : time_limits) {
     if (limit.second < limit.first) return false;
    }
    return true;
  }

public:
  vector<int> enter_time;
  int last_exit_time;
  
  Haircuts (const vector<string>& enter, string& last_exit) {
    for (auto& time : enter) {
      enter_time.emplace_back(parseTime(time));
    }
    last_exit_time = parseTime(last_exit);
    sort(enter_time.begin(),enter_time.end());
  }

  double MaxCut (void) {
    //check if a valid solution (respecting the 5 min constraint exists)
    if(!isValidInput()) return -1;

    //search a lower bound for the max cut
    double lo = 5, hi = last_exit_time;
    for (int i = 0; i < 100; ++i) {
      double m = lo + (hi - lo) / 2;
      if (haircutsCompleted(m)) hi = m;
      else lo = m;
    }
    return lo;
			   			     
  }
  };

int main (void) {
  vector<vector<string>> enters{{"04:22","09:00"},{"09:00","09:22","09:22"},{"09:00","04:00","04:02"}};
  vector<string> exits = {"05:52","10:11","04:09"};
  for (int i = 0; i < enters.size(); ++i) {   
    Haircuts hc(enters[i],exits[i]);
    cout << hc.MaxCut() << endl;
  }
  
}
