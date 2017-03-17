//Rule.cpp
/*
	Definitions of predicates, rules, and facts are stored here, along with definitions
	of their assosciated functions.
*/
#include <iostream>
#include<math.h>

#include "Rule.h"

using namespace std;

//------------------------------------------Rule-----------------------------------------------------//
//Rule is stored in the Rule database.


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
Rule::Rule(string n, int o, vector<string> a, vector<vector<string> > cmps){
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
	output = output + name +"(";
	
	//Rule name and Actors -> string
	for(int i=0; i<actors.size(); i++){
		output += actors.at(i);
		if(i != actors.size()-1) output += ",";
	}
	output += "):- ";

	//Adding Logic
	if(ops == 0) output += "OR ";
	if(ops == 1) output += "AND ";
	
	//Adding the Components
	for(int i=0; i< components.size(); i++){
		output += components.at(i).at(0)+"("; //Getting the component's name
		for(int j=1; j<components.at(i).size(); j++){
			output += components.at(i).at(j);
			if(j != components.at(i).size()-1) output += ",";
		}
		output+=") ";
	}
	output += "\n";
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

