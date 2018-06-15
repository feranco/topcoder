/*

Problem Statement
A busy businessman has a number of equally important tasks which he must accomplish. To decide which of the tasks to perform first, he performs the following operation.

He writes down all his tasks in the form of a circular list, so the first task is adjacent to the last task. He then thinks of a positive number. 
This number is the random seed, which he calls n. Starting with the first task, he moves clockwise (from element 1 in the list to element 2 in the list and so on), 
counting from 1 to n. When his count reaches n, he removes that task from the list and starts counting from the next available task. He repeats this procedure until 
one task remains. It is this last task that he chooses to execute.

Given a list representing the tasks and an n, return the task which the businessman chooses to execute.
*/

#include <list>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

string getTask (vector<string> list, int n) {
		
  std::list<string> tasks(list.begin(), list.end());
  int taskToDelete = list.size()-1;
  auto it = tasks.begin();
    
  for (int i = 0; i < taskToDelete; ++i) {

    //steps to reach the next task to delete
    //n-1 because the current task is taken into account
    int steps = (n-1) % tasks.size();
    
    for (int i = 0; i < steps; ++i, it++) {
      if (it == tasks.end()) it = tasks.begin();
    }

    if (it == tasks.end()) it = tasks.begin();
    auto toDelete = it;
    it = next(toDelete);
    tasks.erase(toDelete);
  }    
  return tasks.front();
}

int main(void) {
  vector<vector<string>> sequences{{"a","b","c","d"},
      {"a","b","c","d","e"},
      	
	{"alpha","beta","gamma","delta","epsilon"},
	  {"a","b"},
	    {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"},
	      {"zlqamum","yjsrpybmq","tjllfea","fxjqzznvg","nvhekxr","am","skmazcey","piklp","olcqvhg","dnpo","bhcfc","y","h","fj","bjeoaxglt","oafduixsz","kmtbaxu",
		  "qgcxjbfx","my","mlhy","bt","bo","q"}
  };
  
  vector<int> nums{2,3,1,1000,17,9000000};

  for (size_t i = 0; i < nums.size(); ++i) {
    cout << getTask(sequences[i],nums[i]) << endl;
  }
}
