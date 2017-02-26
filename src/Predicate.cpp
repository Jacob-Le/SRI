//Predicate.cpp
#include "Predicate.h"

using namespace std;

virtual bool Ops::AND(const bool a, const bool b) {
	return a && b;
}

virtual bool Ops::OR(const bool a, const bool b) {
	return a || b;
}


Predicate::Predicate(){

}

Predicate::Predicate(string relationship, int argCount, ... ){
  Relationship = relationship;
  va_list args;
  va_start(args, argCount);
  for(int i=0; i<argCount; i++) components.push_back(va_arg(args,string));
  va_end(args);
}

bool Predicate::evaluate(vector<string> actors){
  return true;
}

//Constructor
Fact::Fact(vector<string> a, string name){
  vector<string> actors = a;
  string Relationship = name;
}

bool Fact::evaluate(vector<string> actors){
  try{
    //if(this == KB.fetch(Relationship, actors))
    return true;
  }
  catch(const std::invalid_argument& ia){
    cout << "ERROR: Fact does not exist" << ia.what() << "\n" << endl;
    return false;
  }
  return false;
}

Rule::Rule(string n, int count, ...){
  string name = n;
  va_list cmp;
  vector<Predicate*> components;
  for(int i = 0; i < count; i++) components.pushback(va_arg(cmp, Predicate));
  ops = new Ops();
  va_end(cmp);
}

bool Rule::evaluate(vector<string> actors){
  Predicate * first = components[0]; // LHS component to be evaluated
  Predicate * next = components[1]; // RHS component to be evaluated

  //range of actors to take from actors vector
  vector<string> range = vector<string>(components.begin(), components.begin() + first->components.size());

  bool truth = first->evaluate(range); //evaluate using the range of actors that pertain to the particular component
  int count = 0;
  while(next != 0 && count + 1 <= actors.size()){
    //Take range of actors for the next vector
    vector<string> next_range = vector<string>(range.end(), range.end() + next->components.size());
    bool temp = (*ops[count])(truth, next->evaluate(next_range)); //Perform boolean operation using function pointer
    truth = temp;
    count += 1;
    range = next_range;
    next = components[count]; //advance to next one
  }
  return truth;
}

bool Rule::enact(vector<string> actors){
  if(evaluate(actors)){
    //KB.add(new Fact());
    return true;
  }
  return false;
}
/*
bool Rule::operator && (const &Rule r){
  return this->evaluate() && r.evaluate();
}

bool Rule::operator || (const &Rule r){
  return this->evaluate() || r.evaluate();
}
*/

