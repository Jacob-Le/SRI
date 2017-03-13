//Predicate.cpp
/*
	Definitions of predicates, rules, and facts are stored here, along with definitions
	of their assosciated functions.
*/
#include <iostream>
#include<math.h>

#include "Rule.h"

using namespace std;

//------------------------------------------Rule-----------------------------------------------------//
//Rule inherits from Predicate, in turn stored in the Rule database.

//Swaps the values between two rules
//Input: Rule addresses one, two
//Output: void.
void Rule::r_swap(Rule & one, Rule & two){
  using std::swap;
  swap(one.name, two.name);
  swap(one.actors, two.actors);
  swap(one.components, two.components);
  swap(one.ops, two.ops);
}

//Default constructor
Rule::Rule(){
  string name = "";
  //Logical operator associated with this rule represented by an int
  int ops;
  //Vector of actors
  vector<string> actors;
  //Vector of components (Rules or facts) that make up this rule
  vector<vector<string>> components;
}

//Rule constructor that takes in a string as a name, a vector of function pointers that
//emulate boolean operators and a variable number of components.
Rule::Rule(string n, int o, const vector<string> a, const vector<vector<string>> cmps){
  name = n;
  ops = o;
  actors = a;
  components = cmps;
}

//Copy constructor
Rule::Rule(const Rule & r){
  name = r.name;
  actors = r.actors;
  components = r.components;
  ops = r.ops;
}

//Move constructor
Rule::Rule(Rule && r) : Rule(){
  r_swap(*this, r);
}

//Destructor
Rule::~Rule(){

}

//Returns a string representation of the Rule
//Input: void
//Output: String representation of Rule
string Rule::toString(){
    string output = "RULE ";
	output + name;
    for(int i=0; i < components.size(); i++){
        output += components[i]->toString();
		if( (i+1)%2 == 0 ){
			if(ops[i/2] == 0) output += " OR ";
			if(ops[i/2] == 1) output += " AND ";
		}
    }
    return output;
}

//Operator overloads for move and copy assignment
Rule& Rule::operator = (Rule r){
  r_swap(*this, r);
  return *this;
}

Rule& Rule::operator = (Rule && r){
  r_swap(*this, r);
  return *this;
}

//Comparison operator overloads
bool Rule::operator == (const Rule& r){
  return (name == r.name && components == r.components && ops == r.ops);
}

bool Rule::operator != (const Rule& r){
  return !(*this == r);
}
