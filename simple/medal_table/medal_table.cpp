/*
Problem Statement
The Olympic Games in Athens end tomorrow. Given the results of the olympic disciplines, generate and return the medal table.
The results of the disciplines are given as a String[] results, where each element is in the format "GGG SSS BBB". 
GGG, SSS and BBB are the 3-letter country codes (three capital letters from 'A' to 'Z') of the countries winning the gold, silver and bronze medal, respectively.
The medal table is a String[] with an element for each country appearing in results. 
Each element has to be in the format "CCO G S B" (quotes for clarity), where G, S and B are the number of gold, silver and bronze medals won by country CCO, 
e.g. "AUT 1 4 1". The numbers should not have any extra leading zeros. 

Sort the elements by the number of gold medals won in decreasing order. 
If several countries are tied, sort the tied countries by the number of silver medals won in decreasing order. 
If some countries are still tied, sort the tied countries by the number of bronze medals won in decreasing order. 
If a tie still remains, sort the tied countries by their 3-letter code in ascending alphabetical order.

http://community.topcoder.com/stat?c=problem_statement&pm=2922&rd=5855
*/

#include <array>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

struct Country {
  string name;
  array<int,3> medals;
};

vector<string> generate(vector<string> results) {

  //fill hash map with inputs data
  unordered_map<string, array<int,3>> countryToMedals;

  for (const string& result : results) {
    istringstream is{result};
    string country;
    int medalType = 0;
    while (getline(is, country, ' ')) {
      if (countryToMedals.find(country) == countryToMedals.end()) {
	countryToMedals.insert({country,{{0,0,0}}});
      }
      countryToMedals[country][medalType]++;
      medalType++;
    }
  }

  //fill vector with countries-related info
  vector<Country> countries;
  
  for (const auto& country : countryToMedals) {
    countries.push_back({country.first, {{country.second[0], country.second[1], country.second[2]}}});//emplace???
  }

  //sort vector
  sort(countries.begin(), countries.end(), [](const Country& lhs, const Country& rhs){
      //sort in descending order for medals
      if (rhs.medals[0] != lhs.medals[0]) return lhs.medals[0] > rhs.medals[0];
      if (rhs.medals[1] != lhs.medals[1])  return lhs.medals[1] > rhs.medals[1];
      if (rhs.medals[2] != lhs.medals[2])  return lhs.medals[2] > rhs.medals[2];
      //sort in ascending order for names
      return lhs.name < rhs.name;  
    });

  //prepare output
  vector<string> result;

  for (const auto& country : countries) {
    result.push_back(country.name + " " + to_string(country.medals[0]) + " " + to_string(country.medals[1]) + " " + to_string(country.medals[2]));
  }

  return result;
}

int main (void) {
  vector<vector<string>> inputs{{"ITA JPN AUS", "KOR TPE UKR", "KOR KOR GBR", "KOR CHN TPE"}, {"USA AUT ROM"}
    , {"GER AUT SUI", "AUT SUI GER", "SUI GER AUT"}};

  for (auto& input : inputs) {
    auto result = generate(input);
    for (const auto& entry : result) {
      cout << entry << endl;
    }
    cout << "----" << endl;
  }
}
