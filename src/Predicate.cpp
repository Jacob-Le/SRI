//Predicate.cpp
#include "Predicate.h"
#include <iostream>

using namespace std;

//--------------------------------------------Predicate--------------------------------------//

//Swaps the member values between two Predicates
void Predicate::p_swap(Predicate & one, Predicate & two){
  using std::swap;
  swap(one.name, two.name);
  swap(one.components, two.components);
}

//Default Constructor
Predicate::Predicate(){
  string name = "";
  vector<string> components;
}

//Constructor for Predicate, the base class from which both Fact and Rule extend from.
//Takes in a string as a name, and a variable number of string arguments as Actors
Predicate::Predicate(string n, vector<string> actors){
  string name = n;
  vector<string> components = actors;
}

//Copy constructor
Predicate::Predicate(const Predicate & p){
  name = p.name;
  components = p.components;
}

//Move constructor
Predicate::Predicate(Predicate && p) : Predicate(){
  p_swap(*this, p);
}

//Destructor
Predicate::~Predicate(){

}

//Evaluate function.  May need to make this virtual in the future
bool Predicate::evaluate(vector<string> components){
  return true;
}

//Operator overloads for copy and move assignment
Predicate& Predicate::operator = (Predicate p){
  p_swap(*this, p);
  return *this;
}

Predicate& Predicate::operator = (Predicate && p){
  p_swap(*this, p);
  return *this;
}

bool Predicate::AND(bool a, bool b) {
	return a&&b;
}

bool Predicate::OR(bool a, bool b) {
	return a||b;
}





//--------------------------------------------Fact------------------------------------//

//Default Constructor
Fact::Fact(){
  name = "";
  components;
}

//Constructor that takes in a string for a name, and a vector of strings for its components (Actors).
Fact::Fact(string n, vector<string> a){
  components = a;
  name = n;
}

//Copy constructor
Fact::Fact(const Fact & f){
  name = f.name;
  components = f.components;
}

//Move constructor
Fact::Fact(Fact && f) : Fact(){
  p_swap(*this, f);
}

//Evaluate function that takes in a vector of strings that represent the Fact's components
//Will return true if fact exists in the KB, false otherwise
bool Fact::evaluate(vector<string> components){
  try{
    //if(this == KB.fetch(name, components))
    return true;
  }
  catch(const std::invalid_argument& ia){
    cout << "ERROR: Fact does not exist" << ia.what() << "\n" << endl;
    return false;
  }
  return false;
}

//Returns a string representation of the Fact
string Fact::toString(){
    string output = "FACT ";
    output = output + name +"(";
    for(int i=0; i < components.size(); i++){
        output += components[i];
        if(i+1 != components.size()) output += ", ";
    }
    output += ")\n";
    return output;
}


//Operator overloads for Fact copy and move assignment
Fact& Fact::operator = (Fact f){
  p_swap(*this, f);
  return *this;
}

Fact& Fact::operator = (Fact && f){
  p_swap(*this, f);
  return *this;
}

//------------------------------------------Rule-----------------------------------------------------//

//Swaps the values between two rules
void Rule::r_swap(Rule & one, Rule & two){
  using std::swap;
  swap(one.name, two.name);
  swap(one.components, two.components);
  swap(one.ops, two.ops);
}

//Default constructor
Rule::Rule(){
  string name = "";
  //Vector of predicate components (Rules or facts) that make up this rule
  vector<Predicate*> components;
  //Function pointers that point to functions that emulate boolean operators
  vector<bool> ops;
}

//Rule constructor that takes in a string as a name, a vector of function pointers that
//emulate boolean operators and a variable number of components.
Rule::Rule(string n, vector<bool> Logic, vector<Predicate*> cmps){
  string Relationship = n;
  vector<Predicate*> components = cmps;
  vector<bool> ops = Logic; //Operators that compare each component of the rule
}

//Copy constructor
Rule::Rule(const Rule & r){
  name = r.name;
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
//Returns the a boolean representing the Rule's validity.
bool Rule::evaluate(vector<string> actors){
  Predicate * first = components[0]; // LHS component to be evaluated
  Predicate * next = components[1]; // RHS component to be evaluated

  //range of components to take from components vector
  vector<string> range = vector<string>(actors.begin(), actors.begin() + first->components.size());

  bool truth = first->evaluate(range); //evaluate using the range of components that pertain to the particular component
  int count = 0;
  while(next && count + 1 <= components.size()){
    //Take range of components for the next vector
    vector<string> next_range = vector<string>(range.end(), range.end() + next->components.size());
	bool temp;
	if (ops[count] == 0) temp = OR(truth, next->evaluate(next_range));
	else temp = AND(truth, next->evaluate(next_range)); //Perform boolean operation using 0 or 1;
    truth = temp;
    count += 1;
    range = next_range;
    next = components[count]; //advance to next one
  }
  return truth;
}

//If the Rule is valid, adds a Fact representative of the Rule's validity to the KB
//MAKE SURE THAT ACTORS FOR EACH COMPONENT ARE MUTUALLY EXCLUSIVE
bool Rule::enact(vector<string> components){
  if(evaluate(components)){
    //KB.add(new Fact());
    return true;
  }
  return false;
}

//Returns a string representation of the Rule
string Rule::toString(){
    string output = "RULE ";
    output = output + name +"(";
    for(int i=0; i < components.size(); i++){
        output += components[i]->name;
        if(i+1 != components.size()) output += ", ";
    }
    output += ")\n";
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

