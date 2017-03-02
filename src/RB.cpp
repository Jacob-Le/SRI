//Rule database

#include <stdlib.h>
#include <fstream>
#include <algorithm>

#include "RB.h"

using namespace std;

//CONSTRUCTORS-------------------------------------------------------------------------------------------------------------
//Default. Nothing here since rules is declared as empty already.
RB::RB(){
	std::vector<Rule*> rules;
}

//copy constructor
RB::RB(const RB &otherRB) {
	rules = otherRB.rules;
}

//SOURCE CODE---------------------------------------------------------------------------------------------------------------
//Add rules
void RB::Add(Rule * r){
  for(Rule * rule : rules){
    if(rule == r){
			std::cout << "Error: Rule already exists." << "\n" <<std::endl;
			return;
		}
  }
  rules.push_back(r);
}

//Remove rules
Rule* RB::Remove(Rule * r){
  Rule * temp = r;
	vector<Rule*>::iterator pos = find(rules.begin(), rules.end(), r);
  rules.at(distance(rules.begin(), pos))->~Rule();
  rules.erase(pos);
  return temp;
}

//Print as string
std::string RB::toString(){
  std::string s = "";
    for(Rule * rule : rules){
      rule->toString();
    }
    return s;
}

//Load from file
void RB::Load(std::string filepath){
	ofstream myfile;
	myfile.open(filepath);
	if (myfile) std::cout << "Error: File not found." << std::endl;//loading isn't implemented
}

//Save to file
std::string RB::Dump(std::string filepath){

	/*ofstream myfile;
	myfile.open(filepath);
	try {
		if (rule::size == 0) throw throw_exception();

		for (int i = 0; i < rules::size; i++) {
			myfile << toString(vector[i]) << std::endl;
		}
	}
	catch (throw_exception &e) {
		std::cout << e.msg("Error: There are no rules to dump.") << std::endl;
	}*/
}

//DECONSTRUCTOR-----------------------------------------------------------------------------------
//rules destructs itself automatically at the end.
RB::~RB() {

}
