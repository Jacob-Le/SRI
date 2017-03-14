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
	if(rules.count(r->name)==1){
			cout << "Error: Rule already exists.\n";
			return;
	}
	rules[r->name] = r;
}

//Remove rules from database
//Input: Rule point r
//Output: the removed Rule pointer
void RB::Remove(string name){
  rules.erase(name);
}

//Print as string
//Input: void
//Output: returns string representation
string RB::toString(){
  string s = "";
    map<string, Rule*> ::iterator it = rules.begin();
	for(; it!= rules.end(); it++){
      s += it->second->toString();
    }
    return s;
}

//DECONSTRUCTOR-----------------------------------------------------------------------------------
//rules destructs itself automatically at the end.
RB::~RB() {

}