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
  vector<string> actors;
  //Vector of predicate components (Rules or facts) that make up this rule
  vector<vector<string> > components;
  //Function pointers that point to functions that emulate boolean operators
  int ops;
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

//Evaluates the Rule and verifies if the rule is valid or not depending on the validity
//of its components (which can be other Rules or Facts).  Takes in a vector of strings
//that represent actors relevant to each component of the rule.
//MAKE SURE THAT ACTORS FOR EACH COMPONENT ARE MUTUALLY EXCLUSIVE
//Input: Vector of actors
//Output: Rule truth value
// bool Rule::evaluate(vector<string> actors){
//   Predicate * first = components[0]; // LHS component to be evaluated
//   Predicate * next = components[1]; // RHS component to be evaluated
//
//   //range of components to take from components vector
//   vector<string> range = vector<string>(actors.begin(), actors.begin() + first->components.size());
//
//   bool truth = first->evaluate(range); //evaluate using the range of components that pertain to the particular component
//   int count = 0;
//   while(next && count + 1 <= components.size()){
//     //Take range of components for the next vector
//     vector<string> next_range = vector<string>(range.end(), range.end() + next->components.size());
// 	bool temp;
// 	if (ops[count] == 0) temp = OR(truth, next->evaluate(next_range));
// 	else temp = AND(truth, next->evaluate(next_range)); //Perform boolean operation using 0 or 1;
//     truth = temp;
//     count += 1;
//     range = next_range;
//     next = components[count]; //advance to next one
//   }
//   return truth;
// }

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
	output += ")- ";

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

