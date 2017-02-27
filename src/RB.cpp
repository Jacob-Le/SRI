//Rule database

#include <stdlib>
#include <fstream>
#include <iostream>

#include "RB.h"
#ifndef PREDICATE_H
#define PREDICATE_H
#endif


using namespace std;

//EXCEPTION HANDLING------------------------------------------------------------------------------------------------------
//duplicate rules
struct throw_exception : public exception {
	const char * msg() const throw(std::string error) {
		return error;
	}
};

//struct duplicate_rule : public exception {
//	const char * msg() const throw() {
//		return "duplicate rule exception";
//	}
//};
//
//struct empty_rules : public exception {
//	const char * msg() const throw() {
//		return "rules is empty";
//	}
//};
//
//struct file_not_found : public exception {
//	const char * msg() const throw() {
//		return ""
//	}
//};

//CONSTRUCTORS-------------------------------------------------------------------------------------------------------------
//Default. Nothing here since rules is declared as empty already.
RB::RB(){
	std::vector<*Rule> rules;
}

//copy constructor
RB::RB(const RB &otherRB) {
	rules = *otherRB.rules;
}

//SOURCE CODE---------------------------------------------------------------------------------------------------------------
//Add rules
void RB::Add(Rule * r){
  try{
    for(Rule * rule : rules){
      if(rule == r) throw throw_exception();
    }
    rules.push_back(r);
  }catch(throw_exception &e){
      std::cout << "Error: Rule already exists." << "\n" <<std::endl;
    }
}

//Remove rules
Rule* RB::Remove(Rule * r){
  Rule * temp = r;
	vector<Rule*>::iterator pos = find(rules.begin(), rules.end(), r);
  rules.at(pos).~rule();
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
	try {
		if (myfile == 0) throw throw_exception();//loading isn't implemented
	}
	catch (throw_exception &e) {
		std::cout << e.msg("Error: File not found.") << std::endl;
	}
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
