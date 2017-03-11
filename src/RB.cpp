//Rule database
/*
	The database for Rules is defined here. Allows users to add, remove, print, and find Rules
	in the database.
*/

#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <map>

#include "RB.h"

using namespace std;

//CONSTRUCTORS-------------------------------------------------------------------------------------------------------------
//Default. Nothing here since rules is declared as empty already.
RB::RB(){
	map<string, Rule*> rules;
}

//copy constructor
RB::RB(const RB &otherRB) {
	rules = otherRB.rules;
}

//SOURCE CODE---------------------------------------------------------------------------------------------------------------
//Add rules to database
//Input: Rule pointer r
//Output: void
void RB::Add(Rule * r){
  for(Rule * rule : rules){
    if(rule == r){
			std::cout << "Error: Rule already exists." << "\n" <<std::endl;
			return;
		}
  }
  rules.push_back(r);
}

//Remove rules from database
//Input: Rule point r
//Output: the removed Rule pointer
Rule* RB::Remove(Rule * r){
  Rule * temp = r;
  vector<Rule*>::iterator pos = find(rules.begin(), rules.end(), r);
  rules.at(distance(rules.begin(), pos))->~Rule();
  rules.erase(pos);
  return temp;
}

//Print as string
//Input: void
//Output: returns string representation
std::string RB::toString(){
  std::string s = "";
    for(int i=0; i<rules.size();i++){
      s += rules.at(i)->toString();
	  s +='\n';
    }
    return s;
}

//DECONSTRUCTOR-----------------------------------------------------------------------------------
//rules destructs itself automatically at the end.
RB::~RB() {

}
