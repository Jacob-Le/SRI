//Rule database

#include <stdlib.h>
#include "RB.h"
#include <fstream>

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
RB::RB(){

}

//copy constructor
RB::RB(const RB &otherRB) {
	rules = *otherRB.rules;
}

//SOURCE CODE---------------------------------------------------------------------------------------------------------------
//Add rules
void RB::Add(Rule::predicate * r){
  try{
    for(auto const &rule : rules){
      if(rule == r) throw throw_exception();
    }
    rules.pushback(r);
  }catch(duplicate_rule &e){
      std::cout << e.msg("Error: Rule already exists.") <<std::endl;
    }
}

//Remove rules
Rule* RB::Remove(std::string name){
  Rule * temp = nullptr;
  for(int i = 0; i < rules.size(); i++){
    if(rules[i]->name == name){
      temp(rules[i]); //MAKE SURE TO IMPLEMENT COPY CONSTRUCTOR
      rules[i].~rule();
      rules.erase(i);
    }
  }
  return temp;
}

//Print as string
std::string RB::toString(){
  std::string s = "";
    for(auto & rule : rules){
      rule.toString();
    }
    return s;
}

//Load from file
void RB::Load(std::string filepath){
	ofstream myfile;
	myfile.open(filepath);
	try {
		if (myfile == nullptr) throw throw_exception();//loading isn't implemented
	}
	catch (empty_rules &e) {
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
	catch (empty_rules &e) {
		std::cout << e.msg("Error: There are no rules to dump.") << std::endl;
	}*/
}

//DECONSTRUCTOR-----------------------------------------------------------------------------------
RB::~RB() {

}
