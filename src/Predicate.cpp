//Predicate.cpp
#include "Predicate.h"
#include <iostream>

using namespace std;

Predicate::Predicate(){

}

Predicate::Predicate(string n, int argCount, ... ){
  string name = n;
  va_list args;
  va_start(args, argCount);
  for(int i=0; i<argCount; i++) components.push_back(va_arg(args,string));
  va_end(args);
}

Predicate::Predicate(const Predicate & p){
  name = p.name;
  components = p.components;
}

Predicate::Predicate(Predicate && p) : name(0), components(0){
  std::swap(*this, p);
}

bool Predicate::evaluate(vector<string> components){
  return true;
}

void Predicate::swap(Predicate & one, Predicate & two){
  using std::swap;
  swap(one.name, two.name);
  swap(one.components, two.components);
}

Predicate& Predicate::operator = (Predicate p){
  swap(*this, p);
  return *this;
}

Predicate& Predicate::operator = (Predicate && p){
  swap(*this, p);
  return *this;
}

//Constructor
Fact::Fact(string n, vector<string> a){
  vector<string> components = a;
  string name = n;
}

Fact::Fact(const Fact & f){
  name = f.name;
  components = f.components;
}

Fact::Fact(Fact && f) : name(0), components(0){
  std::swap(name, f.name);
  std::swap(components, f.components);
}

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

Fact& Fact::operator = (Fact f){
  swap(*this, f);
  return *this;
}

Fact& Fact::operator = (Fact && f) : name(), components(){
  swap(*this, f)
  return *this;
}

Rule::Rule(string n, vector<bool (*)(bool, bool)> Ops, int count, ...){
  string name = n;
  va_list cmp;
  vector<Predicate*> components;
  for(int i = 0; i < count; i++){
    Predicate p = va_arg(cmp, Predicate);
    components.push_back(&p);
  }
  vector<bool (*)(bool, bool)> ops = Ops; //Operators that compare each component of the rule
  va_end(cmp);
}

Rule::Rule(const Rule & r){
  name = r.name;
  components = r.components;
  ops = r.ops;
}

Rule::Rule(Rule && r) : name(0), ops(0), components(0){
  std::swap(name, r.name);
  std::swap(components, r.components);
  std::swap(ops, r.ops);
}

Rule::~Rule(){

}

bool Rule::evaluate(vector<string> components){
  Predicate * first = components[0]; // LHS component to be evaluated
  Predicate * next = components[1]; // RHS component to be evaluated

  //range of components to take from components vector
  vector<string> range = vector<string>(components.begin(), components.begin() + first->components.size());

  bool truth = first->evaluate(range); //evaluate using the range of components that pertain to the particular component
  int count = 0;
  while(next != 0 && count + 1 <= components.size()){
    //Take range of components for the next vector
    vector<string> next_range = vector<string>(range.end(), range.end() + next->components.size());
    bool temp = (*ops[count])(truth, next->evaluate(next_range)); //Perform boolean operation using function pointer
    truth = temp;
    count += 1;
    range = next_range;
    next = components[count]; //advance to next one
  }
  return truth;
}

bool Rule::enact(vector<string> components){
  if(evaluate(components)){
    //KB.add(new Fact());
    return true;
  }
  return false;
}

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

void Rule::swap(Rule & one, Rule & two){
  using std::swap;
  swap(one.name, two.name);
  swap(one.components, two.components);
  swap(one.ops, two.ops);
}

Rule& Rule::operator = (Rule r){
  swap(*this, r);
  return *this;
}

Rule& Rule::operator = (Rule && r) : name(), components(), ops(){
  swap(*this, r);
  return *this;
}

/*
bool Rule::operator && (const &Rule r){
  return this->evaluate() && r.evaluate();
}

bool Rule::operator || (const &Rule r){
  return this->evaluate() || r.evaluate();
}
*/
